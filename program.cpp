#include "program.h"

#include "console.h"
#include "mouse.h"
#include "keyboard.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    game = new Game();
    //init IO
    Mouse::gi();
    Keyboard::gi();
}

Program::~Program()
{
    delete game;
}
