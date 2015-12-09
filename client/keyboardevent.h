#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <QString>

#include "../common/event.h"
#include "../common/eventdispatcher.h"

class EventDispatcher;

class KeyboardEvent : public Event
{
public:
    static const QString KEY_DOWN;
    static const QString KEY_UP;
    KeyboardEvent(EventDispatcher*, QString, int);
    int keyCode;
};

#endif // KEYBOARDEVENT_H
