#ifndef STATEEVENT_H
#define STATEEVENT_H

#include <QString>

#include "event.h"
#include "state.h"

class StateEvent : public Event
{
public:
    static const QString CHANGE_STATE;
    static const QString TURN_ON;
    static const QString TURN_OFF;
    StateEvent(EventDispatcher*, QString, StateEnum);
    StateEnum state;
};

#endif // STATEEVENT_H
