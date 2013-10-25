#include "program.h"
#include "vector2d.h"
#include "console.h"
#include "matrix.h"

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    Vector2D v1;
    v1.x = 0;
    v1.y = 1;
    Vector2D v2(1,0);
    Console::print(v1);
    Console::print(v1.getLength());
    Console::print(v2.angleBetween(v1));
    Matrix m;
    //m = Matrix::translation(Vector2D(3,5));
    Console::print(m);
}

Program::~Program()
{
    
}
