#include "keyboard.h"

#include "keyboardevent.h"
#include "graphiccore.h"

Keyboard* Keyboard::instance = 0;

Keyboard::Keyboard()
{
    GraphicCore::gi()->addEventListener(this);
}

Keyboard::~Keyboard()
{
    GraphicCore::gi()->removeEventListener(this);
}

void Keyboard::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_UP || event.type == KeyboardEvent::KEY_DOWN)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        dispatchEvent(KeyboardEvent(this, event.type, st->keyCode));
    }
}

Keyboard* Keyboard::gi()
{
    if (instance == 0)
    {
        instance = new Keyboard();
    }
    return instance;
}
