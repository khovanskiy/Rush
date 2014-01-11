#include "program.h"

#include "console.h"
#include "mouse.h"
#include "keyboard.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    game = new Game();
<<<<<<< HEAD
    //init IO
    Mouse::gi();
    Keyboard::gi();
=======
>>>>>>> origin/physicsDebug
}

Program::~Program()
{
    delete game;
}
