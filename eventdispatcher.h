#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <QMutex>
#include <QString>
#include <vector>

#include "eventhandler.h"
#include "event.h"

class EventDispatcher
{
public:
    typedef std::vector<std::pair<EventHandler*, bool>> LIST;

    EventDispatcher();
    void addEventListener(EventHandler*);
    void removeEventListener(EventHandler*);
    void dispatchEvent(const Event&);
private:
    LIST listeners;
    LIST nn;
    int recuirsion_count;
};

#endif // EVENTDISPATCHER_H
