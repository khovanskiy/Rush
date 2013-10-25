#ifndef EVENT_H
#define EVENT_H

#include <QString>

#include "eventdispatcher.h"

class EventDispatcher;

class Event
{
public:
    virtual ~Event() {}
    static const QString INIT;
    static const QString COMPLETE;
    static const QString ENTER_FRAME;
    static const QString CHANGE;
    static const QString ADDED_TO_STAGE;
    static const QString REMOVED_FROM_STAGE;
    Event(EventDispatcher*, QString);
    EventDispatcher* target;
    QString type;
};

//const QString Event::COMPLETE = "complete";

#endif // EVENT_H
