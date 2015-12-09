#include "stateevent.h"

const QString StateEvent::CHANGE_STATE = "changeState";
const QString StateEvent::TURN_ON = "turnOn";
const QString StateEvent::TURN_OFF = "turnOff";

StateEvent::StateEvent(EventDispatcher* target, QString type, StateEnum state) : Event(target, type)
{
    this->state = state;
}
