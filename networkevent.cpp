#include "networkevent.h"

const QString NetworkEvent::CONNECTED = "connected";
const QString NetworkEvent::DISCONNECTED = "disconnected";
const QString NetworkEvent::PROTOCOL = "protocol";

NetworkEvent::NetworkEvent(EventDispatcher* target, QString type) : Event(target, type)
{

}

NetworkEvent::NetworkEvent(EventDispatcher* target, QString type, Protocol* protocol) : Event(target, type)
{
    this->protocol = protocol;
}
