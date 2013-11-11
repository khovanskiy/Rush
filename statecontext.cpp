#include "statecontext.h"

#include "graphiccore.h"
#include "state.h"
#include "stateevent.h"
#include "console.h"
#include "statefactory.h"

StateContext::StateContext()
{
    recuirsion_count = 0;
    GraphicCore::gi()->addEventListener(this);
    push(StateEnum::INIT);
}

void StateContext::Invoke(const Event &event)
{
    ++recuirsion_count;
    if (event.type == Event::ENTER_FRAME)
    {
        for (LIST::iterator i = states.begin(); i != states.end(); ++i)
        {
            if (*i)
            {
                (*i)->render();
            }
        }
    }
    --recuirsion_count;
}

void StateContext::push(StateEnum name)
{
    ++recuirsion_count;
    Console::print("Turn ON");
    if (states.size() > 0)
    {
        states[states.size() - 1]->defocus();
    }
    State* s = 0;
    s = StateFactory::create(name);
    s->setContext(this);
    Console::print(s);
    s->init();
    states.push_back(s);
    s->focus();
    --recuirsion_count;
}

void StateContext::pop()
{
    Console::print("Turn OFF");
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
    Console::print("CHANGE STATE");
    while (states.size() > 0)
    {
        pop();
    }
    push(name);
}