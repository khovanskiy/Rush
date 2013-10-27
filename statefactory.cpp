#include "statefactory.h"

#include "initstate.h"

State* StateFactory::create(StateEnum name)
{
    State* state;
    switch (name)
    {
    //case StateEnum::MAIN_MENU:  state = std::make_shared<MainMenuState>(); break;
    //case StateEnum::GAMEPLAY: state = std::make_shared<GameplayState>(); break;
    //case StateEnum::EXIT: state = std::make_shared<ExitState>(); break;
    //case StateEnum::GAMEOVER: state = std::make_shared<GameOverState>(); break;
    default: state = new InitState();
    }
    return state;
}
