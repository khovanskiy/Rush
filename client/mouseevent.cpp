#include "mouseevent.h"

const QString MouseEvent::CLICK = "click";
const QString MouseEvent::MOUSE_MOVE = "mouseMove";
const QString MouseEvent::MOUSE_WHEEL = "mouseWheel";
const QString MouseEvent::MOUSE_UP = "mouseUp";
const QString MouseEvent::MOUSE_DOWN = "mouseDown";
const QString MouseEvent::MOUSE_OVER = "mouseOver";
const QString MouseEvent::MOUSE_OUT = "mouseOut";

MouseEvent::MouseEvent(EventDispatcher* target, QString type, int x, int y) : Event(target, type)
{
    this->x = x;
    this->y = y;
}

int MouseEvent::getX() const
{
    return x;
}

int MouseEvent::getY() const
{
    return y;
}
