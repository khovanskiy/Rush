#include "initstate.h"
#include "console.h"
#include "state.h"
#include "stateevent.h"
#include "bitmap.h"
#include "mouseevent.h"
#include "stage.h"
#include "math.h"
#include "background.h"
#include "keyboard.h"
#include "keyboardevent.h"

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
    sb->load("D:\\test.jpg");
    Stage::gi()->addChild(sb);
    Keyboard::gi()->addEventListener(this);
}

void InitState::focus()
{
    Console::print("FOCUS");
    //sb->dispatchEvent(Event(sb, Event::CHANGE));
}

void InitState::render()
{
}

void InitState::Invoke(const Event &event)
{
    Console::print(QString("Recieved: ")+event.type);
    if (event.type == KeyboardEvent::KEY_UP)
    {
        context->changeState(StateEnum::INIT);
    }
}

void InitState::defocus()
{
   Console::print("DEFOCUS");
}

void InitState::release()
{
    Console::print("RELEASE");
    Keyboard::gi()->removeEventListener(this);
    Stage::gi()->removeChild(sb);
    delete sb;
    sb = 0;
}
