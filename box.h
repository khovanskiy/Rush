#ifndef PHYSICSBOX_H
#define PHYSICSBOX_H
#include "shape.h"

class Box : public Shape
{
protected:
    double width;
    double length;

public:
    Box(Vector2D const & r, double angle,
        Vector2D const & v, double angular_speed,
        Vector2D const & f, double force_moment,
        Vector2D const & a, double angular_acceleration,
        double mass, double width, double length);
    virtual double getLength();
    virtual double getWidth();
};

#endif // PHYSICSBOX_H
