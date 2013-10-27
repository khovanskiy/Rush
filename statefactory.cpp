#include "statefactory.h"

#include "initstate.h"

std::shared_ptr<State> StateFactory::create(StateEnum name)
{
    std::shared_ptr<State> state;
    switch (name)
    {
    //case StateEnum::MAIN_MENU:  state = std::make_shared<MainMenuState>(); break;
    //case StateEnum::GAMEPLAY: state = std::make_shared<GameplayState>(); break;
    //case StateEnum::EXIT: state = std::make_shared<ExitState>(); break;
    //case StateEnum::GAMEOVER: state = std::make_shared<GameOverState>(); break;
    default: state = std::make_shared<InitState>();
    }
    return state;
}
