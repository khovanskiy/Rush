#ifndef PHYSICSBULLET_H
#define PHYSICSBULLET_H
#include "materialpoint.h"

struct Bullet //: public MaterialPoint
{
    double damage;
    double speed;
    double angle;
    PhysicsObject * owner;

    Bullet();
    //Bullet(Vector2D const & r, double speed, double angle,
           //double mass, double damage, PhysicsObject* owner);
};

#endif // PHYSICSBULLET_H
