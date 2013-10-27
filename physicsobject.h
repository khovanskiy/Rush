#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "vector2d.h"

class PhysicsObject
{
public:
    Vector2D r;
    Vector2D v;
    Vector2D f;
    Vector2D a;
    double angle;
    double angular_speed;
    double force_moment;
    double angular_acceleration;
    double mass, inertia_moment;
    PhysicsObject(Vector2D r, double angle,
                  Vector2D v, double angular_speed,
                  Vector2D f, double force_moment,
                  Vector2D a, double angular_acceleration,
                  double mass, double inertia_moment);
    PhysicsObject();
    virtual void tick(double dt);
};

#endif // PHYSICSOBJECT_H
