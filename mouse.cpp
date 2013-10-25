#include "mouse.h"

#include "graphiccore.h"
#include "background.h"
#include "stage.h"
#include "interface.h"
#include "mouseevent.h"

Mouse* Mouse::instance = 0;

Mouse::Mouse()
{
    GraphicCore::getInstance()->addEventListener(MouseEvent::CLICK, this);
}

Mouse::~Mouse()
{

}

void Mouse::Invoke(const Event &event)
{
    MouseEvent* e = (MouseEvent*)(&event);
    bubbleEvent(MouseEvent(this, event.type, e->getX(), e->getY()));
}

void Mouse::bubbleEvent(const Event &e)
{
    Background::getInstance()->handleEvent(e);
    Stage::getInstance()->handleEvent(e);
    Interface::getInstance()->handleEvent(e);
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
