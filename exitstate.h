#ifndef EXITSTATE_H
#define EXITSTATE_H

#include "state.h"

class ExitState : virtual public State
{
public:
    ExitState();
    void init();
};

#endif // EXITSTATE_H
