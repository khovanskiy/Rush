#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event;

class FunctionProxy;

class EventHandler {
public:
    virtual void Invoke(const Event &) {

    }
};

class FunctionProxy : public EventHandler {
public:
    FunctionProxy(EventHandler *f) {
        this->f = f;
    }

    void Invoke(const Event &event) {
        f->Invoke(event);
    }

private:
    EventHandler *f;
};

#endif // EVENTHANDLER_H
