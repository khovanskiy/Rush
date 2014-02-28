#ifndef NULLSTATE_H
#define NULLSTATE_H

#include <memory>

#include "state.h"
#include "vehicle.h"
#include "statecontext.h"
#include "physicsobjectfactory.h"

class InitState : public State
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
