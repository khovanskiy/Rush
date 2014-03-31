#include "turret.h"
#include "physicsworld.h"
#include "physicsobjectfactory.h"
#include "random.h"

static const double eps = 1e-3;

const int Turret::MACHINEGUN = 0;
const int Turret::ROCKET_LAUNCHER = 1;
const int Turret::SAW = 2;

Turret::Turret(Shape2D *shape, double mass, double inertia_moment,
               double fire_delay, double max_angle, int bullet_type, double scatter)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::TURRET), d_angle(0)
{
    this->max_angle = max_angle;
    this->bullet_type = bullet_type;
    this->firing = false;
    this->fire_delay = fire_delay;
    this->next_shot = fire_delay;
    this->scatter = scatter;
}

Turret::~Turret()
{

}

int Turret::getTurretType() const
{
    return this->turret_type;
}

void Turret::setFiring(bool firing)
{
    this->firing = firing;
}

bool Turret::getFiring() const
{
    return this->firing;
}

void Turret::calculateInnerState(double dt)
{
    PhysicsObject::calculateInnerState(dt);
    next_shot = (dt > next_shot ? 0 : next_shot - dt);

    if (firing && next_shot < eps)
    {
        next_shot = fire_delay;
        dispatchEvent(GameObjectEvent(this, "TURRET_FIRE", Vector2D(0,1)));
    }

    /*if (firing && next_shot < eps)
    {
        next_shot = fire_delay;
        std::vector<PhysicsObject*>* result = new std::vector<PhysicsObject*>();
        if (turret_type == Turret::MACHINEGUN)
        {
            double d_a = scatter * Random::gi().getRandom(-1, 1);
            Vector2D r = local_r;
            Vector2D dr = Vector2D(this->getWidth() * 0.3, this->getHeight() / 2);
            dr.rotate(local_angle);
            r.add(dr);
            Bullet* bullet = PhysicsObjectFactory::createBullet(r, local_angle + d_a, bullet_type, dt);
            bullet->setSource(this);
            result->push_back(bullet);

            d_a = scatter * Random::gi().getRandom(-1, 1);
            r = local_r;
            dr = Vector2D(-this->getWidth() * 0.3, this->getHeight() / 2);
            dr.rotate(local_angle);
            r.add(dr);
            bullet = PhysicsObjectFactory::createBullet(r, local_angle + d_a, bullet_type, dt);
            bullet->setSource(this);
            result->push_back(bullet);
        }
        else if (turret_type == Turret::ROCKET_LAUNCHER)
        {
            Vector2D r = local_r;
            Vector2D dr = Vector2D(0.1 * this->getWidth(), 0.5 * this->getHeight());
            dr.rotate(local_angle);
            r.add(dr);
            double d_a = scatter * Random::gi().getRandom(-1, 1);
            Bullet* bullet = PhysicsObjectFactory::createBullet(r, local_angle + d_a, bullet_type, dt);
            bullet->setSource(this);
            result->push_back(bullet);
        }
        else if (turret_type == Turret::SAW)
        {
            d_angle += 200 * dt;
            Vector2D r = local_r;
            double cur_a = atan2(local_r.y, local_r.x);
            cur_a += 2.3 * asin(1);
            for (int i = 0; i < 17; i++)
            {
                Vector2D nr = r;
                Vector2D dr(0, 1);
                dr.rotate(cur_a);
                dr.mul(5 * dt);
                nr.sub(dr);
                Bullet* bullet = PhysicsObjectFactory::createBullet(nr, cur_a, bullet_type, dt);
                bullet->setSource(this);
                result->push_back(bullet);
                cur_a += asin(1) / 4;
            }
        }
        return result;
    }
    else
    {
        return 0;
    }*/
    return;
}


