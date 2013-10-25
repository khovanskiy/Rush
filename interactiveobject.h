#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "displayobject.h"

class InteractiveObject : public DisplayObject
{
public:
    InteractiveObject();
    virtual void handleEvent(const Event&);
private:
    bool isHovered;
};

#endif // INTERACTIVEOBJECT_H
