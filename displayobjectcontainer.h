#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <QString>
#include <QPainter>
#include <vector>
#include <memory>

#include "interactiveobject.h"

class DisplayObjectContainer : public InteractiveObject
{
public:
    typedef std::shared_ptr<DisplayObject> ELEMENT;
    typedef std::vector<ELEMENT> LIST;
    DisplayObjectContainer();
    virtual ~DisplayObjectContainer();
    void addChild(std::shared_ptr<DisplayObject> child);
    void removeChild(std::shared_ptr<DisplayObject> child);
    bool hasChild(std::shared_ptr<DisplayObject> child) const;
    LIST* getChildrenList() const;
    void render(QPainter*);
    void handleEvent(const Event &);
private:
    LIST* children;
};

#endif // DISPLAYOBJECTCONTAINER_H
