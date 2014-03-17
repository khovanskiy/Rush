#include "mouse.h"

#include "graphiccore.h"
#include "background.h"
#include "stage.h"
#include "interface.h"
#include "mouseevent.h"
#include "console.h"

Mouse* Mouse::instance = 0;

Mouse::Mouse()
{
    GraphicCore::gi()->addEventListener(this);
}

Mouse::~Mouse()
{
    GraphicCore::gi()->removeEventListener(this);
}

void Mouse::Invoke(const Event &event)
{
    if (event.type == MouseEvent::CLICK || event.type == MouseEvent::MOUSE_MOVE || event.type == MouseEvent::MOUSE_DOWN || event.type == MouseEvent::MOUSE_UP || event.type == MouseEvent::MOUSE_WHEEL)
    {
        const MouseEvent* e = static_cast<const MouseEvent*>(&event);
        int nx = e->getX();
        int ny = e->getY();
        if (p.x == nx && p.y == ny && event.type == MouseEvent::MOUSE_UP)
        {
            bubbleEvent(MouseEvent(this, MouseEvent::CLICK, e->getX(), e->getY()));
        }
        bubbleEvent(MouseEvent(this, event.type, e->getX(), e->getY()));
        p.x = nx;
        p.y = ny;
    }
}

const Vector2D& Mouse::position() const
{
    return this->p;
}

void Mouse::bubbleEvent(const Event &e)
{
    Background::gi()->handleEvent(e);
    Stage::gi()->handleEvent(e);
    Interface::gi()->handleEvent(e);
    dispatchEvent(e);
}

Mouse* Mouse::gi()
{
    if (instance == 0)
    {
        instance = new Mouse();
    }
    return instance;
}
