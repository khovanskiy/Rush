#include "thread.h"

Thread::Thread(Runnable *task)
{

}

Thread::~Thread()
{
    Console::print("Thread has been deleted");
}

void Thread::start()
{
    dispatchEvent(Event(this, Event::COMPLETE));
}

ThreadManager* ThreadManager::instance = 0;

ThreadManager::ThreadManager()
{

}

ThreadManager* ThreadManager::gi()
{
    if (instance == 0)
    {
        instance = new ThreadManager();
    }
    return instance;
}

void ThreadManager::Invoke(const Event &event)
{
    if (event.type == event.COMPLETE)
    {
        Thread* st = (Thread*)(event.target);
        delete event.target;
    }
}

void ThreadManager::execute(Thread *thread)
{
    thread->addEventListener(this);
    thread->start();
}
