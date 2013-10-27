#ifndef STATEFACTORY_H
#define STATEFACTORY_H

#include <memory>

#include "state.h"
#include "statecontext.h"

class StateFactory
{
public:
    static std::shared_ptr<State> create(StateEnum);
};

#endif // STATEFACTORY_H
