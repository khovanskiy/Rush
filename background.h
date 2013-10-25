#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "displayobjectcontainer.h"

class Background : public DisplayObjectContainer
{
public:
    static Background* getInstance();
private:
    Background();
    ~Background();
    static Background* instance;
};

#endif // BACKGROUND_H
