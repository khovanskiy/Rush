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

class GameplayState : public State
{
public:
    void init();
    void tick(double dt);
private:
    Bitmap* q;
    Vehicle* car;
    Vehicle* car2;
    VehicleView* b;
    VehicleView* b2;
};

#endif // GAMEPLAYSTATE_H
