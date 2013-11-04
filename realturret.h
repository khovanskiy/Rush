#ifndef REALTURRET_H
#define REALTURRET_H
#include "turret.h"
#include "position.h"

struct RealTurret
{
    Position p;
    Turret turret;

    RealTurret(Position const & p, Turret const & turret);
};

#endif // REALTURRET_H
