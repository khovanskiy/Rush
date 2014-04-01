#include "statecontext.h"

#include "graphiccore.h"
#include "state.h"
#include "stateevent.h"
#include "console.h"
#include "statefactory.h"

StateContext::StateContext()
{
    recuirsion_count = 0;
    push(StateEnum::GAMEPLAY);
}

void StateContext::tick(double dt)
{
    ++recuirsion_count;
    for (LIST::iterator i = states.begin(); i != states.end(); ++i)
    {
        if (*i)
        {
            (*i)->tick(dt);
        }
    }
    --recuirsion_count;
}

void StateContext::push(StateEnum name)
{
    ++recuirsion_count;
    //Console::print("PUSH");
    if (states.size() > 0)
    {
        states[states.size() - 1]->defocus();
    }
    State* s = StateFactory::create(name);
    s->setContext(this);
    s->init();
    states.push_back(s);
    s->focus();
    --recuirsion_count;
}

void StateContext::pop()
{
    //Console::print("POP");
    State* last = states[states.size() - 1];
    last->defocus();
    last->release();
    states.pop_back();
    delete last;
    if (states.size() > 0)
    {
        states[states.size() - 1]->focus();
    }
}

void StateContext::changeState(StateEnum name)
{
    //Console::print("CHANGE");
    while (states.size() > 0)
    {
        pop();
    }
    push(name);
}
