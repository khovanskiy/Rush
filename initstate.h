#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include "bitmap.h"
#include <memory>
#include "vehicle.h"
#include "physicsworld.h"
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
    std::vector<std::pair<Bitmap*, PhysicsObject*>> game_objects;
    Vehicle* dodge;        
};

#endif // NULLSTATE_H
