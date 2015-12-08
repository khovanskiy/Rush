#include "displayobjectcontainer.h"

#include "console.h"

DisplayObjectContainer::DisplayObjectContainer()
{

}

DisplayObjectContainer::~DisplayObjectContainer()
{

}

void DisplayObjectContainer::addChild(DisplayObject* child)
{
    if (child == 0)
    {
        return;
    }
    children.push_back(child);
}

void DisplayObjectContainer::removeChild(DisplayObject* child)
{
    if (child == 0)
    {
        return;
    }
    for (int i = 0; i < children.size(); ++i)
    {
        if (children[i] == child)
        {
            children[i] = children[children.size() - 1];
            children.pop_back();
            break;
        }
    }
}

void DisplayObjectContainer::render(QPainter* render2d, const Matrix& base, bool t, float new_int)
{
    Matrix current = Matrix::mul(getTransform(), base);

    DisplayObject::render(render2d, current, t, new_int);

    for (int i = 0; i < children.size(); ++i)
    {
        children[i]->render(render2d, current, t, new_int);
    }
}

void DisplayObjectContainer::handleEvent(const Event &event)
{
    InteractiveObject::handleEvent(event);
    for (int i = 0; i < children.size(); ++i)
    {
        DisplayObject* d = children[i];
        if (InteractiveObject* io = dynamic_cast<InteractiveObject*>(d))
        {
            io->handleEvent(event);
        }
    }
}
