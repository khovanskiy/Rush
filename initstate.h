#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include "statecontext.h"
#include "gameworld.h"
#include "mapview.h"
#include "physicsworld.h"
#include "uivehiclecontroller.h"

class InitState : public State
{
public:
    InitState();
    void init();
    void render(const RenderData&);
    void tick(double dt);
    void release();
    void Invoke(const Event &event);
private:
    PhysicsWorld* physics_world;
    GameWorld* game_world;
    MapView* map_view;
    UIVehicleController* controls;
};

#endif // NULLSTATE_H
