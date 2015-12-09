#include "keyboardevent.h"

const QString KeyboardEvent::KEY_DOWN = "keyDown";
const QString KeyboardEvent::KEY_UP = "keyUp";

KeyboardEvent::KeyboardEvent(EventDispatcher* target, QString type, int keyCode) : Event(target, type)
{
    this->keyCode = keyCode;
}
