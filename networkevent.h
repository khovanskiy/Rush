#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include "event.h"

class Protocol;

class NetworkEvent : public Event
{
public:
    static const QString CONNECTED;
    static const QString DISCONNECTED;
    static const QString PROTOCOL;

    NetworkEvent(EventDispatcher* target, QString type);
    NetworkEvent(EventDispatcher* target, QString type, Protocol* protocol);

    Protocol* protocol;
};

#endif // NETWORKEVENT_H
