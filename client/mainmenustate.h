#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../common/state.h"
#include "bitmap.h"

class MainMenuState : public State, EventHandler
{
public:
    MainMenuState();
    void init();
    void render(const RenderData &);
    void release();
    void Invoke(const Event &);
private:
    Bitmap* button_new_game;
    Bitmap* button_exit;
};

#endif // MAINMENUSTATE_H
