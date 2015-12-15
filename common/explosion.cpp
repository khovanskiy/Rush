#include "explosion.h"

const int Explosion::SMALL = 0;
const int Explosion::MEDIUM = 1;
const int Explosion::LARGE = 2;

Explosion::Explosion(int id, Shape2D *shape, double mass, double inertia_moment,
                     double start_radius, double end_radius, double time,
                     double explosion_impulse, int explosion_type)
    : PhysicsObject(id, shape, mass, inertia_moment, PhysicsObject::EXPLOSION)
{
    this->start_radius = start_radius;
    this->end_radius = end_radius;
    this->time_to_live = time;
    this->time = time;
    this->explosion_type = explosion_type;
    this->explosion_impulse = explosion_impulse;
}

int Explosion::getExplosionType()
{
    return this->explosion_type;
}

void Explosion::tick(double dt)
{
    time_to_live -= dt;
    if (time_to_live < 0)
    {
        invalidate();
    }
    else
    {
        double radius = start_radius + (end_radius - start_radius) * (time - time_to_live) / time;
        this->setShape(new Circle2D(this->getCoordinates(), radius, this->getAngle()));
    }
}

Collision Explosion::solveCollisionWith(PhysicsObject *other, const Point2D &center)
{
    return Collision(shape->cross(other->getShape()).center.toVector(),
                     shape->getGeometryCenter().getVectorTo(other->getShape()->getGeometryCenter()),
                     other->getSpeed(), Vector2D(this->explosion_impulse, 0), other);
}

void Explosion::applyCollision(const Collision &collision, double dt)
{
}

bool Explosion::isProjectile()
{
    return true;
}
