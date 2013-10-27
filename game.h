#ifndef GAME_H
#define GAME_H

#include "statecontext.h"

class StateContext;

class Game
{
public:
    Game();
    ~Game();
private:
    StateContext* state_context;
};

#endif // GAME_H
