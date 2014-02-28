#include "statefactory.h"

#include "initstate.h"
#include "gameplaystate.h"
#include "exitstate.h"

State* StateFactory::create(StateEnum name)
{
    State* state;
    switch (name)
    {
    //case StateEnum::MAIN_MENU:  state = new MainMenuState(); break;
    //case AuthState login|password
    case StateEnum::GAMEPLAY: state = new GameplayState(); break;
    case StateEnum::EXIT: state = new ExitState(); break;
    //case StateEnum::GAMEOVER: state = std::make_shared<GameOverState>(); break;
    default: state = new InitState();
    }
    return state;
}
