#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include <memory>
#include "statecontext.h"
#include "physicsobjectfactory.h"

class InitState : virtual public State
{
public:
    InitState();
    virtual ~InitState();
    void init();
    void focus();
    void tick(double dt);
    void defocus();
    void release();
    void Invoke(const Event &event);


    void calculateView();

private:
    double time;
    Vehicle* dodge;
};

#endif // NULLSTATE_H
