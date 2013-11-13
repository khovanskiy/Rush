#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "vector2d.h"
#include <vector>

class PhysicsObject
{
public:
    PhysicsObject();
    virtual void tick(double dt) = 0;
    virtual Vector2D getCoordinates() = 0;
    virtual Vector2D getSpeed() = 0;
    virtual double getAngle() = 0;
    virtual double getAngularSpeed() = 0;
    virtual void setCoordinates(Vector2D const & r) = 0;
    virtual void setSpeed(Vector2D const & v) = 0;
    //virtual std::vector<PhysicsObject*> getCollidingItems() = 0;
    //virtual bool collidesWithItem(PhysicsObject* object) = 0;
};

#endif // PHYSICSOBJECT_H
