#include "turret.h"
#include "physicsworld.h"

static const double eps = 1e-3;

Turret::Turret()
{
    this->firing = false;
}

Turret::Turret(Turret const & turret)    
{
    this->setAngle(0);
    this->setBullet(turret.bullet_mass, turret.bullet_speed, turret.bullet_type);
    this->setFireDelay(turret.fire_delay);
    this->setFiring(false);
    this->setMaxAngle(turret.max_angle);
    this->setPosition(turret.r);
}

void Turret::setPosition(Vector2D r)
{
    this->r = r;
}

void Turret::setMaxAngle(double max_angle)
{
    this->max_angle = max_angle;
}

void Turret::setAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

void Turret::setBullet(double bullet_mass, double bullet_speed, BulletType bullet_type)
{
    this->bullet_type = bullet_type;
    this->bullet_mass = bullet_mass;
    this->bullet_speed = bullet_speed;
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

std::vector<Bullet*> Turret::calculateFireAndForces(double dt)
{
    next_shot = (dt > next_shot ? 0 : next_shot - dt);
    if (!firing)
    {
        f.x = 0;
        f.y = 0;
        force_moment = 0;
        return std::vector<Bullet*>();
    }
    else
    {
        if (next_shot < eps)
        {
            next_shot = fire_delay;
            Vector2D speed(0, bullet_speed);
            speed.rotate(angle);
            f = speed;
            f.mul(-bullet_mass / dt);
            force_moment = r.cross(f);
            std::vector<Bullet*> result;
            Bullet* bullet = new Bullet(r, speed, bullet_mass, bullet_type, dt);
            result.push_back(bullet);
            return result;
        }
        else
        {
            return std::vector<Bullet*>();
        }
    }
}


