#ifndef REALENGINE_H
#define REALENGINE_H
#include "vehicleengine.h"
#include "position.h"

struct RealEngine
{
    Position p;
    VehicleEngine engine;

    RealEngine(Position const & p, VehicleEngine const & engine);
};

#endif // REALENGINE_H
