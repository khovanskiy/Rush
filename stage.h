#ifndef STAGE_H
#define STAGE_H

#include "displayobjectcontainer.h"

class Stage : public DisplayObjectContainer
{
public:
    static Stage* gi();
private:
    Stage();
    ~Stage();
    static Stage* instance;
};

#endif // STAGE_H
