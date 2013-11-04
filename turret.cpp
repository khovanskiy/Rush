#include "turret.h"

Turret::Turret(Vector2D const & r, double max_angle)
    : r(r)
{
    this->max_angle = max_angle;
    this->firing = false;
}

Turret::Turret(Turret const & turret)
    : r(turret.r)
{
    this->max_angle = turret.max_angle;
    this->firing = turret.firing;
}

void Turret::setAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

void Turret::setBullet(Bullet const & bullet)
{
    this->bullet = bullet;
}

void Turret::setFireDelay(double fire_delay)
{
    this->fire_delay = fire_delay;
    this->next_shot = fire_delay;
}

void Turret::setFiring(bool firing)
{
    this->firing = firing;
}

void Turret::calculateFireAndForces(double dt)
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


