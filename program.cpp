#include "program.h"
#include "vector2d.h"
#include "console.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    Vector2D v1;
    v1.x = 1;
    v1.y = 2;
    Console::print(v1);
}

Program::~Program()
{
    
}
