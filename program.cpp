#include "program.h"

#include "vector2d.h"
#include "console.h"
#include "matrix.h"
#include "event.h"
#include "eventdispatcher.h"
#include "eventhandler.h"


class A
{
public:
    A()
    {
        renderEvent = new EventDispatcher();
    }

    EventDispatcher* renderEvent;
};

class B : public EventHandler
{
public:
    B()
    {

    }
    virtual void Invoke(const Event &event)
    {
        Console::print(event.type + " :: message is recieved");
    }
};

Program::Program(QWidget *parent) : QMainWindow(parent)
{
    core = GraphicCore::gi();
    ticks_timer = new QTimer(this);
    ticks_timer->setSingleShot(false);
    QObject::connect(ticks_timer, SIGNAL(timeout()), this, SLOT(onTick()));
    ticks_timer->start(0);

    game = new Game();
}

void Program::onTick()
{
    core->render();
}

Program::~Program()
{
    
}
