#include "mouse.h"

#include "graphiccore.h"
#include "background.h"
#include "stage.h"
#include "interface.h"
#include "mouseevent.h"

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
    MouseEvent* e = (MouseEvent*)(&event);
    bubbleEvent(MouseEvent(this, event.type, e->getX(), e->getY()));
}

void Mouse::bubbleEvent(const Event &e)
{
    Background::gi()->handleEvent(e);
    Stage::gi()->handleEvent(e);
    Interface::gi()->handleEvent(e);
    dispatchEvent(e);
}

Mouse* Mouse::getInstance()
{
    if (instance == 0)
    {
        instance = new Mouse();
    }
    return instance;
}
