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

#define WAIT_VEHICLE 1
#define NEED_INIT_VEHICLE 2
#define INITED 3

class GameplayState : public State, public EventHandler
{
public:
    void init();
    void render(const RenderData &);
    void tick(double dt);
    void Invoke(const Event &);
    void release();
private:
    int current_id_player;
    int current_id_vehicle;
    int current_state;
    Vehicle* current_vehicle;
    GameWorld* game_world;
    MapView* map_view;

    UIVehicleController* controls;
    CameraController* camera_controls;
    NetworkServer* server;
};

#endif // GAMEPLAYSTATE_H
