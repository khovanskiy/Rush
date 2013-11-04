#ifndef REALBODY_H
#define REALBODY_H
#include "vehiclebody.h"
#include "position.h"

struct RealBody
{
    Position p;
    VehicleBody body;

    RealBody(Position const & p, VehicleBody const & body);
};

#endif // REALBODY_H
