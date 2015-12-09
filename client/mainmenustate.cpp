#include "mainmenustate.h"

#include "mouse.h"
#include "interface.h"

MainMenuState::MainMenuState()
{
}

void MainMenuState::init()
{
    button_new_game = new Bitmap();
    button_exit = new Bitmap();
    button_new_game->load("DATA\\Textures\\Buttons\\new_game_hover.png");
    button_exit->load("DATA\\Textures\\Buttons\\exit_hover.png");
    button_new_game->setPosition(Vector2D(100,100));
    button_exit->setPosition(Vector2D(100,200));
    button_exit->addEventListener(this);
    Interface::gi()->addChild(button_new_game);
    Interface::gi()->addChild(button_exit);
}

void MainMenuState::Invoke(const Event &event)
{
    if (event.type == MouseEvent::CLICK)
    {
        Console::print("Click");
        if (event.target == button_new_game)
        {
            context->changeState(StateEnum::GAMEPLAY);
        }
        else if (event.target == button_exit)
        {
            context->changeState(StateEnum::EXIT);
        }
    }
}

void MainMenuState::render(const RenderData &render_data)
{
    button_new_game->render(render_data.render2d, Matrix(), false, render_data.interpolation);
    button_exit->render(render_data.render2d, Matrix(), false, render_data.interpolation);
}

void MainMenuState::release()
{
    Interface::gi()->removeChild(button_new_game);
    Interface::gi()->removeChild(button_exit);
    delete button_exit;
    delete button_new_game;
}
