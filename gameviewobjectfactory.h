#ifndef GAMEVIEWOBJECTFACTORY_H
#define GAMEVIEWOBJECTFACTORY_H
#include "gameviewobject.h"

class GameViewObjectFactory
{
    GameViewObjectFactory();

public:
    static GameViewObject* createGameViewObject(GameModelObject* game_model_object);
};

#endif // GAMEVIEWOBJECTFACTORY_H
