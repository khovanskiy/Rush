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
    DisplayObjectContainer();
    virtual ~DisplayObjectContainer();

    void addChild(DisplayObject* child);
    void removeChild(DisplayObject* child);

    void render(QPainter*, const Matrix&, bool, float);

    void handleEvent(const Event &);
private:
    std::vector<DisplayObject*> children;
};

#endif // DISPLAYOBJECTCONTAINER_H
