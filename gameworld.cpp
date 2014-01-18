#include "gameworld.h"
#include "console.h"
#include <QElapsedTimer>

GameWorld::~GameWorld()
{
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        delete *i;
    }
    deleteInvalidObjects();
}

void GameWorld::deleteInvalidObjects()
{
    int num = to_delete.size();
    if (num > 0)
    {
        GameModelObject** ptr = &to_delete.front();
        for (int i = 0; i < num; i++)
        {
            delete ptr[i];
        }
        to_delete.clear();
    }
}

void GameWorld::getNewObjects()
{
    PhysicsWorld& pw = PhysicsWorld::gi();
    std::vector<ObjectData*> v = pw.popNewObjects();
    int num = v.size();
    if (num > 0)
    {
        ObjectData** ptr = &v.front();
        for (int i = 0; i < num; i++)
        {
            GameModelObject* game_object = new GameModelObject(ptr[i]);
            new_objects.push_back(game_object);
            game_objects.push_back(game_object);
        }
    }
}

void GameWorld::updateObjects(double dt)
{
    const int num = game_objects.size();
    if (num > 0)
    {
        GameModelObject** ptr = &game_objects.front();
        std::vector<GameModelObject*> remained;
        for (int i = 0; i < num; i++)
        {
            ptr[i]->update(dt, Vector2D(0, 0), 0);
            if (ptr[i]->isValid())
            {
                remained.push_back(ptr[i]);
            }
            else
            {
                to_delete.push_back(ptr[i]);
            }
        }
        game_objects = remained;
    }
}

std::vector<GameModelObject*> GameWorld::popNewObjects()
{
    std::vector<GameModelObject*> result(this->new_objects);
    new_objects.clear();
    return result;
}

void GameWorld::clear()
{
    int num = game_objects.size();
    if (num > 0)
    {
        GameModelObject** ptr = &game_objects.front();
        for (int i = 0; i < num; i++)
        {
            delete ptr[i];
        }
        new_objects.clear();
    }
    game_objects.clear();
    PhysicsWorld::gi().clear();
}

void GameWorld::tick(double dt)
{
    deleteInvalidObjects();
    PhysicsWorld& pw = PhysicsWorld::gi();
    pw.tick(dt);
    updateObjects(dt);
    getNewObjects();
}



