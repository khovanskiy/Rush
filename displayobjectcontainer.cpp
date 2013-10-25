#include "displayobjectcontainer.h"

#include "console.h"

DisplayObjectContainer::DisplayObjectContainer()
{
    children = new std::vector<ELEMENT>();
}

DisplayObjectContainer::~DisplayObjectContainer()
{
    while (children->size() > 0)
    {
        children->back().reset();
        children->pop_back();
    }
    delete children;
}

void DisplayObjectContainer::addChild(std::shared_ptr<DisplayObject> child)
{
    children->push_back(child);
}

void DisplayObjectContainer::removeChild(std::shared_ptr<DisplayObject> child)
{
    //children->erase(std::remove(children->begin(),children->end(), child));
    for (LIST::iterator i = children->begin(); i != children->end(); i++)
    {
        Console::print((*i).get());
        if ((*i).get() == child.get())
        {
            children->erase(i);
            return;
        }
    }
}

bool DisplayObjectContainer::hasChild(std::shared_ptr<DisplayObject> child) const
{
    return find(children->begin(),children->end(), child) != children->end();
}

void DisplayObjectContainer::render(QPainter* render2d)
{
    LIST list = *children;
    for (LIST::iterator it = list.begin(); it != list.end(); it++)
    {
        ELEMENT d = *it;
        d->render(render2d);
    }
}

std::vector<std::shared_ptr<DisplayObject>>* DisplayObjectContainer::getChildrenList() const
{
    return children;
}
void DisplayObjectContainer::handleEvent(const Event &event)
{
    InteractiveObject::handleEvent(event);
    LIST list = *children;
    for (LIST::iterator it = list.begin(); it != list.end(); it++)
    {
        std::shared_ptr<DisplayObject> d = *it;
        if (InteractiveObject* io = dynamic_cast<InteractiveObject*>(d.get()))
        {
            io->handleEvent(event);
        }
    }
}
