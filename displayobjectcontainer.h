#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <QString>
#include <QPainter>
#include <vector>
#include <memory>

#include "interactiveobject.h"
#include "matrix.h"

class DisplayObjectContainer : public InteractiveObject
{
public:
    typedef DisplayObject* ELEMENT;
    typedef std::vector<ELEMENT> LIST;
    DisplayObjectContainer();
    virtual ~DisplayObjectContainer();
    void addChild(DisplayObject* child);
    void removeChild(DisplayObject* child);
    bool hasChild(DisplayObject* child) const;
    //LIST* getChildrenList() const;
    void render(QPainter*, const Matrix&, bool, float);
    void handleEvent(const Event &);
private:
    LIST children;
};

#endif // DISPLAYOBJECTCONTAINER_H
