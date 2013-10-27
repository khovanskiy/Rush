#ifndef STATECONTEXT_H
#define STATECONTEXT_H

#include <vector>
#include <memory>
#include <QMutex>

#include "eventhandler.h"
#include "state.h"

class State;
enum StateEnum;

class StateContext : public EventHandler
{
public:
    StateContext();
    void push(StateEnum name);
    void pop();
    void changeState(StateEnum name);
    void Invoke(const Event &event);
private:
    typedef std::vector<std::shared_ptr<State>> LIST;
    LIST states;
};

#endif // STATECONTEXT_H
