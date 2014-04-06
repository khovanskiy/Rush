#ifndef STATECONTEXT_H
#define STATECONTEXT_H

#include <vector>

#include "eventhandler.h"
#include "state.h"
#include "renderdata.h"

enum StateEnum;
class State;

class StateContext
{
public:
    StateContext();
    void push(StateEnum name);
    void pop();
    void changeState(StateEnum name);
    void render(const RenderData&);
    void tick(double dt);
private:
    typedef std::vector<State*> LIST;
    LIST states;
};

#endif // STATECONTEXT_H
