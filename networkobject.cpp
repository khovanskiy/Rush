#include "networkobject.h"

NetworkObject::NetworkObject()
{
    valid = true;
}

void NetworkObject::invalidate()
{
    valid = false;
}

bool NetworkObject::isValid()
{
    return valid;
}
