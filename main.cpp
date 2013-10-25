#include "program.h"
#include <QApplication>
#include "console.h"


struct A
{
    virtual void tick()
    {
        Console::print("A struct");
    }
};

struct B : A
{
    virtual void tick()
    {
        A::tick();
        Console::print("B struct");
    }
};

struct C : B
{
    virtual void tick()
    {
        B::tick(); // super.tick();
        Console::print("C struct");
    }
};

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    Program w;
    w.show();
    
    return a.exec();*/
    Console::print("Test");
    A* c = new C();
    c->tick();
    return 0;
}
