#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "state.h"

#include "vehicle.h"
#include "bitmap.h"
#include "stage.h"
#include "interface.h"
#include "background.h"
#include "physicsworld.h"
#include "vehicleview.h"
#include "networkserver.h"
#include "mouse.h"
#include "mouseevent.h"
#include "uivehiclecontroller.h"
#include "cameracontroller.h"
#include "mapview.h"
#include "camera.h"

class GameplayState : public State
{
public:
    void init();
    void tick(double dt);
    void Invoke(const Event &);
    void release();
private:
    Vehicle* player;
    PhysicsWorld* physics_world;
    GameWorld* game_world;
    Vehicle* car;
    MapView* map_view;
    UIVehicleController* controls;
    CameraController* camera_controls;
    NetworkServer* server;
    Bitmap* b;
};

#endif // GAMEPLAYSTATE_H
