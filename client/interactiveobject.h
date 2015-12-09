#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "displayobject.h"

class InteractiveObject : public DisplayObject
{
public:
    InteractiveObject();
    virtual void handleEvent(const Event&);
protected:
    virtual void onMouseMove(const Event&) {}
    virtual void onMouseOver(const Event&) {}
    virtual void onMouseOut(const Event&) {}
    virtual void onMouseWheel(const Event&) {}
    virtual void onMouseClick(const Event&) {}
private:
    bool isHovered;
};

#endif // INTERACTIVEOBJECT_H
