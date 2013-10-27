#include "physicsturret.h"

PhysicsTurret::PhysicsTurret(Vector2D r, double max_angle)
{
    this->r = r;
    this->max_angle = max_angle;
    this->firing = false;
}

void PhysicsTurret::setAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

void PhysicsTurret::setBullet(PhysicsBullet bullet)
{
    this->bullet = bullet;
}

void PhysicsTurret::setFireDelay(double fire_delay)
{
    this->fire_delay = fire_delay;
    this->next_shot = fire_delay;
}

void PhysicsTurret::setFiring(bool firing)
{
    this->firing = firing;
}

void PhysicsTurret::calculateFireAndForces(double dt)
{
    if (!firing)
    {
        next_shot = (dt > next_shot ? 0 : next_shot - dt);
        f.x = 0;
        f.y = 0;
        force_moment = 0;
    }
    else
    {
        while (dt > 0)
        {
            if (next_shot < dt)
            {
                dt -= next_shot;
                next_shot = fire_delay;
                //Create bullet.

            }
            else
            {

            }
        }
    }
}


