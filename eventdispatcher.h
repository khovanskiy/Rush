#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <QMutex>
#include <QString>
#include <vector>
#include <map>

#include "function.h"
#include "event.h"

class EventDispatcher
{
public:
    typedef std::vector<Function*> LIST;
    EventDispatcher();
    virtual ~EventDispatcher();
    void addEventListener(QString type, Function* func);
    void removeEventListener(QString type, Function* func);
    void dispatchEvent(const Event&);
private:
    QMutex mutex;
    std::map<QString, LIST*> listeners;
};

#endif // EVENTDISPATCHER_H
