#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include "bitmap.h"
#include <memory>
#include "vehicle.h"

class InitState : virtual public State
{
public:
    InitState();
    virtual ~InitState();
    void init();
    void focus();
    void render();
    void defocus();
    void release();

    void Invoke(const Event &event);
private:
    Bitmap* sb;
    Vehicle* v;    
};

#endif // NULLSTATE_H
