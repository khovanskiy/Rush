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
    x = -1;
    y = -1;
}

Mouse::~Mouse()
{
    GraphicCore::gi()->removeEventListener(this);
}

void Mouse::Invoke(const Event &event)
{
    if (event.type == MouseEvent::CLICK || event.type == MouseEvent::MOUSE_MOVE || event.type == MouseEvent::MOUSE_DOWN || event.type == MouseEvent::MOUSE_UP || event.type == MouseEvent::MOUSE_WHEEL)
    {
        MouseEvent* e = (MouseEvent*)(&event);
        //Console::print(QVariant(e->getX()).toString()+" "+QVariant(e->getY()).toString());
        int nx = e->getX();
        int ny = e->getY();
        if (x == nx && y == ny && event.type == MouseEvent::MOUSE_UP)
        {
            bubbleEvent(MouseEvent(this, MouseEvent::CLICK, e->getX(), e->getY()));
        }
        bubbleEvent(MouseEvent(this, event.type, e->getX(), e->getY()));
        x = nx;
        y = ny;
    }
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
