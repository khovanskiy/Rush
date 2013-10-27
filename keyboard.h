#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "eventdispatcher.h"
#include "eventhandler.h"

class Keyboard : public EventDispatcher, public EventHandler
{
public:
    static Keyboard* gi();
    void Invoke(const Event &event);
private:
    Keyboard();
    ~Keyboard();
    static Keyboard* instance;
};

#endif // KEYBOARD_H
