#ifndef PHYSICSTURRET_H
#define PHYSICSTURRET_H
#include "bullet.h"
#include <vector>
struct Turret
{
    Vector2D r;
    double max_angle;
    double bullet_mass, bullet_speed;
    int bullet_id;

    double angle;
    double fire_delay, next_shot;
    bool firing;
    Vector2D f;
    double force_moment;


    Turret();
    Turret(Turret const & turret);
    void setPosition(Vector2D r);
    void setMaxAngle(double max_angle);
    void setBullet(double bullet_mass, double bullet_speed, int bullet_id);
    void setFireDelay(double fire_delay);
    void setFiring(bool firing);
    void setAngle(double percent);
    std::vector<Bullet*> calculateFireAndForces(double dt);
};

#endif // PHYSICSTURRET_H
