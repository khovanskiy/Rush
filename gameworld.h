#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "console.h"
#include "gamemodelobject.h"

class GameWorld : public GameModelObject
{

public:
    GameWorld();
    virtual ~GameWorld();
    void tick(double dt);
private:
    std::vector<GameModelObject*> unused;
};

#endif // GAMEWORLD_H
