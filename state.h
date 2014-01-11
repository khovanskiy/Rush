#ifndef STATE_H
#define STATE_H

#include "eventhandler.h"
#include "eventdispatcher.h"
#include "console.h"

class StateContext;
enum StateEnum
{
    INIT, MAIN_MENU, GAMEPLAY, EXIT, GAMEOVER
};

class State : public EventDispatcher, public EventHandler
{
public:
    State() { locker = true; }
    virtual ~State() { Console::print("State is deleted"); } // Без этого delete State* не сделать
    virtual void init() {}
    virtual void focus() {}
<<<<<<< HEAD
    virtual void tick(double) {}
=======
    virtual void tick(double dt) {}
>>>>>>> origin/physicsDebug
    virtual void defocus() {}
    virtual void release() {}
    virtual void Invoke(const Event&) {}
    QString name;
    void setContext(StateContext* c) { if (locker) {context = c; locker = false;} }
protected:
    StateContext* context;
private:
    bool locker;
};

#endif // STATE_H
