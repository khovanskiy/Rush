#ifndef PHYSICSPOINT_H
#define PHYSICSPOINT_H
#include "physicsobject.h"

class MaterialPoint : public PhysicsObject
{
protected:
    Vector2D r;
    Vector2D v;
    Vector2D f;
    Vector2D a;
    double mass;

public:
    MaterialPoint(Vector2D const & r,
                  Vector2D const & v,
                  Vector2D const & f,
                  Vector2D const & a,
                  double mass);
    virtual void tick(double dt);
    virtual Vector2D getCoordinates();
    virtual Vector2D getSpeed();
    virtual double getAngle();
    virtual double getAngularSpeed();
    virtual void setCoordinates(Vector2D const & r);
    virtual void setSpeed(Vector2D const & v);
};

#endif // PHYSICSPOINT_H
