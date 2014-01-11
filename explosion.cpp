#include "explosion.h"

const QString Explosion::SMALL = "small";
const QString Explosion::MEDIUM = "medium";
const QString Explosion::LARGE = "large";

Explosion::Explosion(Shape2D *shape, double mass, double inertia_moment,
                     double start_radius, double end_radius, double time,
                     double explosion_impulse, QString explosion_type)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::EXPLOSION)
{
    this->start_radius = start_radius;
    this->end_radius = end_radius;
    this->time_to_live = time;
    this->time = time;
    this->explosion_type = explosion_type;
    this->explosion_impulse = explosion_impulse;
}

QString Explosion::getExplosionType()
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

CrossingResult2D Explosion::collidesWith(PhysicsObject *other)
{
    if ((other->getType() == PhysicsObject::BULLET)
            || (other->getType() == PhysicsObject::EXPLOSION))
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }
    else
    {
        return (this->shape->cross(other->getShape()));
    }
}

Collision Explosion::solveCollisionWith(PhysicsObject *other, const Point2D &center)
{
    return Collision(this->getShape()->cross(other->getShape()).center.toVector(),
                     other->getSpeed(), Vector2D(this->explosion_impulse, 0), other);
}

void Explosion::applyCollision(const Collision &collision, double dt)
{
}
