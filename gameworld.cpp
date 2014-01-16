#include "gameworld.h"
#include "console.h"

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
    for (auto i = to_delete.begin(); i != to_delete.end(); i++)
    {
        delete *i;
    }
    to_delete.clear();
}

void GameWorld::getNewObjects()
{
    PhysicsWorld& pw = PhysicsWorld::gi();
    std::vector<ObjectData*> v = pw.popNewObjects();
    for (auto i = v.begin(); i != v.end(); i++)
    {
        GameModelObject* game_object = new GameModelObject(*i);
        new_objects.push_back(game_object);
        game_objects.push_back(game_object);
    }
}

void GameWorld::updateObjects(double dt)
{
    std::vector<GameModelObject*> remained;
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        (*i)->update(dt, Vector2D(0, 0), 0);
        if ((*i)->isValid())
        {
            remained.push_back(*i);
        }
        else
        {
            to_delete.push_back(*i);
        }
    }
    game_objects = remained;
}

std::vector<GameModelObject*> GameWorld::popNewObjects()
{
    std::vector<GameModelObject*> result(this->new_objects);
    new_objects.clear();
    return result;
}

void GameWorld::clear()
{
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        delete *i;
    }
    new_objects.clear();
    game_objects.clear();
    Console::print("Game objects cleared.");
    PhysicsWorld::gi().clear();
    Console::print("Game world cleared.");
}

void GameWorld::tick(double dt)
{
    deleteInvalidObjects();
    PhysicsWorld& pw = PhysicsWorld::gi();
    pw.tick(dt);
    updateObjects(dt);
    getNewObjects();
}



