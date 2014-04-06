#include "initstate.h"
#include "console.h"
#include "state.h"
#include "stateevent.h"
#include "bitmap.h"
#include "mouseevent.h"
#include "keyboard.h"
#include "mouse.h"
#include "keyboardevent.h"
#include "random"
#include "physicsobjectfactory.h"

InitState::InitState()
{
    game_world = new GameWorld();
    physics_world = new PhysicsWorld();
    map_view = new MapView(game_world);
}

void InitState::init()
{
    Vehicle* vehicle = PhysicsObjectFactory::createVehicle(1, 1);
    vehicle->addTurret(PhysicsObjectFactory::createTurret(2,1));
    game_world->add(vehicle);
    physics_world->add(vehicle);
    controls = new UIVehicleController(vehicle);
}

void InitState::tick(double dt)
{
    physics_world->tick(dt);
    game_world->tick(dt);
}

void InitState::render(const RenderData& render_data)
{
    map_view->render(render_data);
}

void InitState::Invoke(const Event &)
{

}

void InitState::release()
{

}
