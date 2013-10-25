#include "physicsobject.h"

PhysicsObject::PhysicsObject(double x, double y, double angle,
                             double vx, double vy, double angular_speed,
                             double fx, double fy, double force_moment,
                             double ax, double ay, double angular_acceleration,
                             double mass, double inertia_moment)
{
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->vx = vx;
    this->vy = vy;
    this->angular_speed = angular_speed;
    this->fx = fx;
    this->fy = fy;
    this->force_moment = force_moment;
    this->ax = ax;
    this->ay = ay;
    this->angular_acceleration = angular_acceleration;
    this->mass = mass;
    this->inertia_moment = inertia_moment;
}

PhysicsObject::tick(double dt)
{
    x += vx * dt;
    y += vy * dt;
    angle += angular_speed * dt;
    vx += ax * dt;
    vy += ay * dt;
    angular_speed += angular_acceleration * dt;
    ax = fx / mass;
    ay = fy / mass;
    angular_acceleration = force_moment / inertia_moment;
}
