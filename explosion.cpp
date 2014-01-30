#include "explosion.h"

const int Explosion::SMALL = 0;
const int Explosion::MEDIUM = 1;
const int Explosion::LARGE = 2;

Explosion::Explosion(Shape2D *shape, double mass, double inertia_moment,
                     double start_radius, double end_radius, double time,
                     double explosion_impulse, int explosion_type)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::EXPLOSION)
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
        dynamic_cast<Circle2D*>(this->getShape())->setRadius(radius);
    }
}

Collision Explosion::solveCollisionWith(PhysicsObject *other, const Point2D &center)
{
    double k = 1 - center.getDistTo(Point2D(getCoordinates())) / end_radius;
    Vector2D impulse = center.toVector();
    impulse.sub(other->getMassCenter());
    impulse.setLength(k * k * explosion_impulse);
    return Collision(center.toVector(), impulse, Vector2D(0, 0), 0.0, other);
}

void Explosion::applyCollision(const Collision &collision, double dt)
{
}

bool Explosion::isProjectile()
{
    return true;
}
