#include "gameworld.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{
    for (int i = 0; i < unused.size(); ++i)
    {
        delete unused[i];
    }
    for (int i = 0; i < inners.size(); ++i)
    {
        inners[i]->invalidate();
        delete inners[i];
    }
    Console::print("GameWorld is deleted");
}

void GameWorld::tick(double dt)
{
    for (int i = 0; i < unused.size(); ++i)
    {
        delete unused[i];
    }
    unused.clear();
    for (int i = 0; i < inners.size(); ++i)
    {
        if (inners[i]->isValid())
        {
            inners[i]->tick(dt);
        }
        else
        {
            unused.push_back(inners[i]);
            inners[i] = inners[inners.size() - 1];
            inners.pop_back();
            --i;
        }
    }
}
