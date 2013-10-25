#include "program.h"
#include "vector2d.h"
#include "console.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    Vector2D v1;
    v1.x = 0;
    v1.y = 1;
    Vector2D v2(1,0);
    Console::print(v1);
    Console::print(v1.getLength());
    Console::print(v2.angleBetween(v1));
}

Program::~Program()
{
    
}
