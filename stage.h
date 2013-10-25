#ifndef STAGE_H
#define STAGE_H

#include "displayobjectcontainer.h"

class Stage : public DisplayObjectContainer
{
public:
    static Stage* getInstance();
private:
    Stage();
    ~Stage();
    static Stage* instance;
};

#endif // STAGE_H
