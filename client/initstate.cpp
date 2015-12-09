#include "initstate.h"
#include "../common/console.h"
#include "../common/state.h"
#include "../common/stateevent.h"
#include "mouseevent.h"
#include "keyboard.h"
#include "mouse.h"
#include "keyboardevent.h"
#include "random"
#include "../common/physicsobjectfactory.h"
#include "../common/physicsworld.h"

InitState::InitState()
{

}

void InitState::init()
{
    physics_world = new PhysicsWorld();
    game_world = new GameWorld();
    map_view = new MapView(game_world);

    game_world->add(new Terrain(1));

    Obstacle* wall = PhysicsObjectFactory::createObstacle(2, 0);
    wall->setCoordinates(Vector2D(10,10));
    game_world->add(wall);
    physics_world->add(wall);

    Vehicle* vehicle = PhysicsObjectFactory::createVehicle(2000, 1);
    game_world->add(vehicle);
    physics_world->add(vehicle);
    vehicle->setCoordinates(Vector2D(5, 5));
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
    delete controls;
    delete map_view;
    delete game_world;
    delete physics_world;
}
