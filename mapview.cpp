/*#include "mapview.h"
#include "console.h"
#include <QElapsedTimer>

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
    int num = (int)to_delete.size();
    if (num > 0)
    {
        GameViewObject** ptr = &to_delete.front();
        for (int i = 0; i < num; i++)
        {
            removeFromScene(ptr[i]);
            delete ptr[i];
        }
        to_delete.clear();
    }
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
    int num = (int)inner_objects.size();
    if (num > 0)
    {
        GameViewObject** ptr = &inner_objects.front();
        for (int i = 0; i < num; i++)
        {
            removeFromScene(ptr[i]);
        }
    }
}

void MapView::addToScene(GameViewObject *game_view_object)
{
    Stage::gi()->addChild(game_view_object->getBitmap());
    std::vector<GameViewObject*> inner_objects = game_view_object->getInnerObjects();
    int num = (int)inner_objects.size();
    if (num > 0)
    {
        GameViewObject** ptr = &inner_objects.front();
        for (int i = 0; i < num; i++)
        {
            addToScene(ptr[i]);
        }
    }
}

void MapView::tick(double dt)
{
    deleteInvalidObjects();
    GameWorld& gw = GameWorld::gi();
    gw.tick(dt);
    std::vector<GameViewObject*> remained;
    int num = game_view_objects.size();
    if (num > 0)
    {
        GameViewObject** ptr = &game_view_objects.front();
        for (int i = 0; i < num; i++)
        {
            if (ptr[i]->isValid())
            {
                remained.push_back(ptr[i]);
            }
            else
            {
                to_delete.push_back(ptr[i]);
            }
        }
        game_view_objects = remained;
    }
    std::vector<GameModelObject*> v = gw.popNewObjects();
    num = v.size();
    if (num > 0)
    {
        GameModelObject** ptr = &v.front();
        for (int i = 0; i < num; i++)
        {
            addGameViewObject(GameViewObjectFactory::createGameViewObject(ptr[i]));
        }
    }
}

void MapView::updateView(double scale, Vector2D d_r, double d_angle, Vector2D center)
{
    int num = game_view_objects.size();
    if (num > 0)
    {
        GameViewObject** ptr = &game_view_objects.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->update(scale, d_r, d_angle, center);
        }
    }
}

void MapView::clear()
{
    int num = game_view_objects.size();
    if (num > 0)
    {
        GameViewObject** ptr = &game_view_objects.front();
        for (int i = 0; i < num; i++)
        {
            to_delete.push_back(ptr[i]);
        }
        game_view_objects.clear();
    }
    GameWorld::gi().clear();
}*/
