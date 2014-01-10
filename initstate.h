#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include "bitmap.h"
#include <memory>
#include "vehicle.h"
#include "statecontext.h"

class InitState : virtual public State
{
public:
    InitState();
    virtual ~InitState();
    void init();
    void focus();
    void tick(double dt);
    void defocus();
    void release();
    void Invoke(const Event &event);
private:
    Bitmap* dodgeBitmap;
    Bitmap* ferrariBitmap;
    Vehicle* dodge;
    Vehicle* ferrari;
    Vehicle* current;
};

#endif // NULLSTATE_H
