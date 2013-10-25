#ifndef INTERFACE_H
#define INTERFACE_H

#include "displayobjectcontainer.h"

class Interface : public DisplayObjectContainer
{
public:
    static Interface* gi();
private:
    Interface();
    virtual ~Interface();
    static Interface* instance;
};

#endif // INTERFACE_H
