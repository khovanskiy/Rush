#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <QString>

#include "event.h"
#include "eventdispatcher.h"

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
