#include "interactiveobject.h"

#include "mouseevent.h"
#include "keyboardevent.h"
#include "console.h"

InteractiveObject::InteractiveObject()
{
    isHovered = false;
}

void InteractiveObject::handleEvent(const Event &event)
{
    if (event.type == MouseEvent::MOUSE_MOVE || event.type == MouseEvent::CLICK || event.type == MouseEvent::MOUSE_DOWN || event.type == MouseEvent::MOUSE_UP)
    {
        MouseEvent* st = (MouseEvent*)(&event);
        bool hit = hitTestPoint(st->getX(), st->getY());
        if (event.type == MouseEvent::MOUSE_MOVE)
        {
            onMouseMove(event);
            if (isHovered)
            {
                if (!hit)
                {
                    onMouseOut(event);
                    dispatchEvent(MouseEvent(this, MouseEvent::MOUSE_OUT, st->getX(), st->getY()));
                    isHovered = !isHovered;
                }

            }
            else
            {
                if (hit)
                {
                    onMouseOver(event);
                    dispatchEvent(MouseEvent(this, MouseEvent::MOUSE_OVER, st->getX(), st->getY()));
                    isHovered = !isHovered;
                }
            }
        }
        else if (hit)
        {
            dispatchEvent(MouseEvent(this, event.type, st->getX(), st->getY()));
        }
    }
}
