#include "mapview.h"
#include "console.h"

MapView::~MapView()
{
    for (auto i = game_view_objects.begin(); i != game_view_objects.end(); i++)
    {
        to_delete.push_back(*i);
    }
    deleteInvalidObjects();
}

void MapView::deleteInvalidObjects()
{
    for (auto i = to_delete.begin(); i != to_delete.end(); i++)
    {
        removeFromScene(*i);
        delete *i;
    }
    to_delete.clear();
}

void MapView::addGameViewObject(GameViewObject *game_view_object)
{
    addToScene(game_view_object);
    game_view_objects.push_back(game_view_object);
}

void MapView::removeFromScene(GameViewObject *game_view_object)
{
    Stage::gi()->removeChild(game_view_object->getBitmap());
    std::vector<GameViewObject*> inner_objects = game_view_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        removeFromScene(*i);
    }
}

void MapView::addToScene(GameViewObject *game_view_object)
{
    Stage::gi()->addChild(game_view_object->getBitmap());
    std::vector<GameViewObject*> inner_objects = game_view_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        addToScene(*i);
    }
}

void MapView::tick(double dt)
{
    deleteInvalidObjects();
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
            to_delete.push_back(*i);
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
    Console::print("Start clearing...");
    for (auto i = game_view_objects.begin(); i != game_view_objects.end(); i++)
    {
        to_delete.push_back(*i);
    }
    game_view_objects.clear();
    Console::print("View objects cleared.");
    GameWorld::gi().clear();
    Console::print("Mapview cleared.");    
    Console::print("Finished clearing.");
}
