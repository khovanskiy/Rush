#ifndef MOUSE_H
#define MOUSE_H

#include "eventdispatcher.h"

class Mouse : public EventDispatcher, public EventHandler
{
public:
    static Mouse* getInstance();
    void Invoke(const Event&);
private:
    Mouse();
    ~Mouse();
    void bubbleEvent(const Event&);
    static Mouse* instance;
};

#endif // MOUSE_H
