#include "program.h"

#include "vector2d.h"
#include "console.h"
#include "matrix.h"
#include "event.h"
#include "eventdispatcher.h"
#include "eventhandler.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    game = new Game();
}

Program::~Program()
{
    delete game;
}
