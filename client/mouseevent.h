#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QString>

#include "../common/event.h"
#include "../common/eventdispatcher.h"

class MouseEvent : public Event
{
public:
    static const QString CLICK;
    static const QString MOUSE_MOVE;
    static const QString MOUSE_WHEEL;
    static const QString MOUSE_UP;
    static const QString MOUSE_DOWN;
    static const QString MOUSE_OVER;
    static const QString MOUSE_OUT;
    MouseEvent(EventDispatcher*, QString, int, int);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
};

#endif // MOUSEEVENT_H
