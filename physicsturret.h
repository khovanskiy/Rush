#ifndef PHYSICSTURRET_H
#define PHYSICSTURRET_H
#include "physicsbullet.h"
#include "vector2d.h"

struct PhysicsTurret
{
    Vector2D r;
    double max_angle;

    double angle;
    double fire_delay, next_shot;
    PhysicsBullet bullet;
    bool firing;
    Vector2D f;
    double force_moment;


    PhysicsTurret(Vector2D r, double max_angle);
    void setAngle(double percent);
    void setFireDelay(double fire_delay);
    void setBullet(PhysicsBullet bullet);
    void setFiring(bool firing);
    void calculateFireAndForces(double dt);
};

#endif // PHYSICSTURRET_H
