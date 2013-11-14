#ifndef STATECONTEXT_H
#define STATECONTEXT_H

#include <vector>
#include <memory>
#include <QMutex>

#include "eventhandler.h"
#include "state.h"

class StateContext
{
public:
    StateContext();
    void push(StateEnum name);
    void pop();
    void changeState(StateEnum name);
    void tick(double dt);
private:
    typedef std::vector<State*> LIST;
    LIST states;
    int recuirsion_count;
};

#endif // STATECONTEXT_H
