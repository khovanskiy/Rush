#ifndef PHYSICSCIRCLE_H
#define PHYSICSCIRCLE_H
#include "shape.h"

class Circle : public Shape
{
public:
    Circle(Vector2D const & r, double angle,
           Vector2D const & v, double angular_speed,
           Vector2D const & f, double force_moment,
           Vector2D const & a, double angular_acceleration,
           double mass, double radius);
};

#endif // PHYSICSCIRCLE_H
