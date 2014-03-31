#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "console.h"
#include "gamemodelobject.h"

class GameWorld : public GameModelObject
{
    GameWorld();
    virtual ~GameWorld();
public:
    static GameWorld& gi()
    {
        static GameWorld instance;
        return instance;
    }
    void tick(double dt);
};

#endif // GAMEWORLD_H
