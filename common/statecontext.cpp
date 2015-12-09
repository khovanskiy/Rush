#include "statecontext.h"

#include "stateevent.h"
#include "../client/statefactory.h"

StateContext::StateContext()
{
    push(StateEnum::GAMEPLAY);
}

void StateContext::render(const RenderData& render_data)
{
    for (int i = 0; i < states.size(); ++i)
    {
        states[i]->render(render_data);
    }
}

void StateContext::tick(double dt)
{
    for (int i = 0; i < states.size(); ++i)
    {
        states[i]->tick(dt);
    }
}

void StateContext::push(StateEnum name)
{
    if (states.size() > 0)
    {
        states[states.size() - 1]->defocus();
    }
    State* s = StateFactory::create(name);
    s->setContext(this);
    s->init();
    states.push_back(s);
    s->focus();
}

void StateContext::pop()
{
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
    while (states.size() > 0)
    {
        pop();
    }
    push(name);
}
