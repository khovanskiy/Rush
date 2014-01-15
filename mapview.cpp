#include "mapview.h"
#include "console.h"

MapView::~MapView()
{
    clear();
}

void MapView::addGameViewObject(GameViewObject *game_view_object)
{
    Stage::gi()->addChild(game_view_object->getBitmap());
    game_view_objects.push_back(game_view_object);
    std::vector<GameViewObject*> inner_objects = game_view_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        addGameViewObject(*i);
    }
}

void MapView::removeGameViewObject(GameViewObject *game_view_object)
{
    Console::print("Removing object...");
    Stage::gi()->removeChild(game_view_object->getBitmap());
    std::vector<GameViewObject*> inner_objects = game_view_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        removeGameViewObject(*i);
    }
    Console::print("Object removed.");
}

void MapView::tick(double dt)
{
    GameWorld& gw = GameWorld::gi();
    gw.tick(dt);
    std::vector<GameModelObject*> v = gw.popNewObjects();
    for (auto i = v.begin(); i != v.end(); i++)
    {
        addGameViewObject(GameViewObjectFactory::createGameViewObject(*i));
    }
    std::vector<GameViewObject*> remained;
    for (auto i = game_view_objects.begin(); i != game_view_objects.end(); i++)
    {
        if ((*i)->isValid())
        {
            remained.push_back(*i);
        }
        else
        {
            removeGameViewObject(*i);
            delete *i;
        }
    }
    game_view_objects = remained;
}

void MapView::updateView(double scale, Vector2D d_r, double d_angle, Vector2D center)
{
    for (auto i = game_view_objects.begin(); i != game_view_objects.end(); i++)
    {
        (*i)->update(scale, d_r, d_angle, center);
    }
}

void MapView::clear()
{
    for (auto i = game_view_objects.begin(); i != game_view_objects.end(); i++)
    {
        removeGameViewObject(*i);
        delete *i;
    }
    game_view_objects.clear();
    Console::print("View objects cleared.");
    GameWorld::gi().clear();
    Console::print("Mapview cleared.");
}
