#include "eventdispatcher.h"

#include <QThread>

#include "console.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::addEventListener(QString type, Function* func)
{
    if (func == 0)
    {
        Console::print("FATAL ERROR!!!!");
        return;
    }
    if (!listeners[type])
    {
        listeners[type] = new std::vector<Function*>();
    }
    listeners[type]->push_back(func);
}

void EventDispatcher::removeEventListener(QString type, Function* func)
{
    if (!listeners[type])
    {
        return;
    }
    LIST* list = listeners[type]; // А если разыменовать, то list.erase() нифига не удаляет =(
    LIST::iterator it = find(list->begin(), list->end(), func);
    if (it != list->end())
    {
        list->erase(it);
    }
}

void EventDispatcher::dispatchEvent(const Event& event)
{
    if (!listeners[event.type])
    {
        return;
    }
    LIST list = *listeners[event.type];
    mutex.lock();
    for (LIST::iterator it = list.begin(); it != list.end(); it++)
    {
        (*it)->Invoke(event);
    }
    mutex.unlock();
}
