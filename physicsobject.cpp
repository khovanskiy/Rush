#include "physicsobject.h"

PhysicsObject::PhysicsObject(Vector2D r, double angle,
                             Vector2D v, double angular_speed,
                             Vector2D f, double force_moment,
                             Vector2D a, double angular_acceleration,
                             double mass, double inertia_moment)
{
    this->r = r;
    this->angle = angle;
    this->v = v;
    this->angular_speed = angular_speed;
    this->f = f;
    this->force_moment = force_moment;
    this->a = a;
    this->angular_acceleration = angular_acceleration;
    this->mass = mass;
    this->inertia_moment = inertia_moment;
}

PhysicsObject::PhysicsObject()
{

}

void PhysicsObject::tick(double dt)
{
    r.x += v.x * dt;
    r.y += v.y * dt;
    angle += angular_speed * dt;
    v.x += a.x * dt;
    v.y += a.y * dt;
    angular_speed += angular_acceleration * dt;
    a.x = f.x / mass;
    a.y = f.y / mass;
    angular_acceleration = force_moment / inertia_moment;
}
