#ifndef PHYSICSCIRCLE_H
#define PHYSICSCIRCLE_H
#include "shape.h"

class Circle : public Shape
{
protected:
    double radius;

public:
    Circle(Vector2D const & r, double angle,
           Vector2D const & v, double angular_speed,
           Vector2D const & f, double force_moment,
           Vector2D const & a, double angular_acceleration,
           double mass, double radius);
    virtual double getRadius();
};

#endif // PHYSICSCIRCLE_H
