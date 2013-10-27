#ifndef PHYSICSBULLET_H
#define PHYSICSBULLET_H
#include "physicsobject.h"

struct PhysicsBullet : PhysicsObject
{
    double damage;
    double speed;
    //PhysicsBullet(double mass, double damage, double x, double y, double speed, double angle);
    PhysicsBullet();
};

#endif // PHYSICSBULLET_H
