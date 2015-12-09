#ifndef STATEFACTORY_H
#define STATEFACTORY_H

#include <memory>

#include "../common/state.h"
#include "../common/statecontext.h"

class StateFactory
{
public:
    static State* create(StateEnum);
};

#endif // STATEFACTORY_H
