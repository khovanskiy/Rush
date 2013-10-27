#include "initstate.h"
#include "console.h"
#include "state.h"
#include "stateevent.h"
#include "bitmap.h"
#include "mouseevent.h"
#include "stage.h"
#include "math.h"
#include "background.h"

InitState::InitState()
{
    Console::print("CONSTRUCTOR");
}

InitState::~InitState()
{
    Console::print("DESTRUCTOR");
}

void InitState::init()
{
    Console::print("INIT");
    sb = new Bitmap();
    sb->addEventListener(this);
    sb->load("D:\\test2.jpg");
    Background::gi()->addChild(sb);
}

void InitState::focus()
{
    Console::print("FOCUS");
    sb->dispatchEvent(Event(sb, Event::CHANGE));
}

void InitState::render()
{
}

void InitState::Invoke(const Event &event)
{
    Console::print(QString("Recieved: ")+event.type);
    if (event.type == Event::COMPLETE)
    {
        sb->removeEventListener(this);
    }
}

void InitState::defocus()
{
   Console::print("DEFOCUS");
}

void InitState::release()
{
    Console::print("RELEASE");
}
