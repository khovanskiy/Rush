#include "game.h"

Game::Game()
{
    state_context = new StateContext();
}

Game::~Game()
{
    delete state_context;
}


