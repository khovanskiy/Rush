#ifndef PHYSICSTURRET_H
#define PHYSICSTURRET_H
#include "bullet.h"
#include "vector2d.h"

struct Turret
{
    Vector2D r;
    double max_angle;

    double angle;
    double fire_delay, next_shot;
    Bullet bullet;
    bool firing;
    Vector2D f;
    double force_moment;


    Turret(Vector2D const & r, double max_angle);
    Turret(Turret const & turret);
    void setFireDelay(double fire_delay);
    void setBullet(Bullet const & bullet);
    void setFiring(bool firing);
    void setAngle(double percent);
    void calculateFireAndForces(double dt);
};

#endif // PHYSICSTURRET_H
