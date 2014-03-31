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
#include "mapview.h"

class GameplayState : public State
{
public:
    void init();
    void tick(double dt);
    void Invoke(const Event &);
private:
    MapView* map_view;
    Bitmap* point;
    Vehicle* car;
    Vehicle* car2;
    VehicleView* b;
    VehicleView* b2;
    NetworkServer* server;
};

#endif // GAMEPLAYSTATE_H
