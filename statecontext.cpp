#include "statecontext.h"

#include "graphiccore.h"
#include "state.h"
#include "stateevent.h"
#include "console.h"
#include "statefactory.h"

StateContext::StateContext()
{
    GraphicCore::gi()->addEventListener(this);
    push(StateEnum::INIT);
}

void StateContext::Invoke(const Event &event)
{
    if (event.type == Event::ENTER_FRAME)
    {
        for (LIST::iterator it = states.begin(); it != states.end(); it++)
        {
            if (*it != 0)
            {
                it->get()->render();
            }
        }
    }
}

void StateContext::push(StateEnum name)
{
    Console::print("Turn ON");
    if (states.size() > 0)
    {
        states[states.size() - 1].get()->defocus();
    }
    std::shared_ptr<State> s = StateFactory::create(name);
    s.get()->setContext(this);
    states.push_back(s);
    s.get()->init();
    s.get()->focus();
}

void StateContext::pop()
{
    Console::print("Turn OFF");
    std::shared_ptr<State> last = states[states.size() - 1];
    last.get()->defocus();
    last.get()->release();
    states.pop_back();
    last.reset();
    if (states.size() > 0)
    {
        states[states.size() - 1].get()->focus();
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
