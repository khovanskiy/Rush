#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "eventdispatcher.h"
#include "function.h"

class Keyboard : public EventDispatcher, public Function
{
public:
    static Keyboard* getInstance();
    void Invoke(const Event &event);
private:
    Keyboard();
    ~Keyboard();
    static Keyboard* instance;
};

#endif // KEYBOARD_H
