#include "interactiveobject.h"

#include "mouseevent.h"
#include "keyboardevent.h"

InteractiveObject::InteractiveObject()
{
    isHovered = false;
}

void InteractiveObject::handleEvent(const Event &event)
{
    if (event.type == MouseEvent::CLICK)
    {
        MouseEvent* st = (MouseEvent*)(&event);
        if (hitTestPoint(st->getX(), st->getY()))
        {
            dispatchEvent(MouseEvent(this, MouseEvent::CLICK, st->getX(), st->getY()));
        }
    }
    else
    {
        dispatchEvent(event);
    }
}
