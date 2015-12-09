#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>

#include "common/eventdispatcher.h"
#include "common/console.h"

class Runnable : public QObject
{
    Q_OBJECT
public:
    virtual void run();
};

class Thread : public EventDispatcher
{
public:
    Thread(Runnable *task);
    virtual ~Thread();
    void start();
};

class ThreadManager : public EventHandler
{
public:
    ThreadManager();
    void execute(Thread *thread);
    void Invoke(const Event &event);
    static ThreadManager* gi();
private:
    static ThreadManager* instance;
};

#endif // THREAD_H
