#ifndef NETWORKOBJECT_H
#define NETWORKOBJECT_H

#include "common/eventdispatcher.h"

class NetworkObject : public EventDispatcher
{
public:
    NetworkObject();
    bool isValid();
    void invalidate();
private:
    bool valid;
};

#endif // NETWORKOBJECT_H
