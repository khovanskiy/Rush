#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "gamemodelobject.h"

class GameWorld
{
    std::vector<GameModelObject*> new_objects;
    std::vector<GameModelObject*> game_objects;
    std::vector<GameModelObject*> to_delete;

    GameWorld()
    {
    }
    GameWorld(GameWorld const &);
    void operator=(GameWorld const&);
    ~GameWorld();

    void getNewObjects();
    void deleteInvalidObjects();
    void updateObjects(double dt);

public:
    static GameWorld& gi()
    {
        static GameWorld instance;
        return instance;
    }
    std::vector<GameModelObject*> popNewObjects();
    void tick(double dt);
    void clear();
};

#endif // GAMEWORLD_H
