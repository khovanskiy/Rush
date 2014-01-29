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
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void DisplayObjectContainer::removeAll()
{
    children.clear();
}

bool DisplayObjectContainer::hasChild(DisplayObject* child) const
{
    if (child == 0)
    {
        return false;
    }
    return find(children.begin(), children.end(), child) != children.end();
}

void DisplayObjectContainer::render(QPainter* render2d, const Matrix& base)
{
    Matrix current = Matrix::mul(*getLocalMatrix(), base);
    for (LIST::iterator it = children.begin(); it != children.end(); it++)
    {
        ELEMENT d = *it;
        d->render(render2d, current);
    }
}

void DisplayObjectContainer::handleEvent(const Event &event)
{
    InteractiveObject::handleEvent(event);
    for (LIST::iterator it = children.begin(); it != children.end(); it++)
    {
        DisplayObject* d = *it;
        if (InteractiveObject* io = dynamic_cast<InteractiveObject*>(d))
        {
            io->handleEvent(event);
        }
    }
}
