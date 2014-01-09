#include "explosion.h"

const QString Explosion::SMALL = "small";
const QString Explosion::MEDIUM = "medium";
const QString Explosion::LARGE = "large";

Explosion::Explosion(Shape2D *shape, double mass, double inertia_moment,
                     double start_radius, double end_radius, double time,
                     QString explosion_type)
    : PhysicsObject(shape, mass, inertia_moment)
{
    this->start_radius = start_radius;
    this->end_radius = end_radius;
    this->time_to_live = time;
    this->time = time;
    this->explosion_type = explosion_type;
    this->physics_object_type = PhysicsObject::EXPLOSION;
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

bool Explosion::collidesWith(PhysicsObject *other)
{
    return (other->getType() != PhysicsObject::BULLET)
            && (other->getType() != PhysicsObject::EXPLOSION)
            && (this->shape->cross(other->getShape()).crossing);
}

void Explosion::applyCollisions(const std::vector<Collision> &collisions)
{
}
