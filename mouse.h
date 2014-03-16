#ifndef MOUSE_H
#define MOUSE_H

#include "eventdispatcher.h"
#include "vector2d.h"

class Mouse : public EventDispatcher, public EventHandler
{
public:
    static Mouse* gi();
    const Vector2D& position() const;
    void Invoke(const Event&);
private:
    Mouse();
    ~Mouse();
    void bubbleEvent(const Event&);
    static Mouse* instance;
    Vector2D p;
};

#endif // MOUSE_H
