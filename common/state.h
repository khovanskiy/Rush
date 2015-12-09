#ifndef STATE_H
#define STATE_H

#include "eventhandler.h"
#include "eventdispatcher.h"
#include <QPainter>
#include "statecontext.h"
#include "renderdata.h"

class StateContext;

class State : public EventDispatcher
{
public:
    State() { locker = true; }
    virtual ~State() {} // Без этого delete State* не сделать
    virtual void init() {}
    virtual void focus() {}
    virtual void tick(double) {}
    virtual void render(const RenderData&) {}
    virtual void defocus() {}
    virtual void release() {}
    QString name;
    void setContext(StateContext* c) { if (locker) {context = c; locker = false;} }
protected:
    StateContext* context;
private:
    bool locker;
};

#endif // STATE_H
