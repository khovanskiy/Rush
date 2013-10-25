#include "keyboard.h"

#include "keyboardevent.h"
#include "graphiccore.h"

Keyboard* Keyboard::instance = 0;

Keyboard::Keyboard()
{
    GraphicCore::getInstance()->addEventListener(KeyboardEvent::KEY_UP, this);
}

Keyboard::~Keyboard()
{

}

void Keyboard::Invoke(const Event &event)
{
    KeyboardEvent* st = (KeyboardEvent*)(&event);
    dispatchEvent(KeyboardEvent(this, event.type, st->keyCode));
}

Keyboard* Keyboard::getInstance()
{
    if (instance == 0)
    {
        instance = new Keyboard();
    }
    return instance;
}
