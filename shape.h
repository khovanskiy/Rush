#ifndef SHAPE_H
#define SHAPE_H
#include "materialpoint.h"

class Shape : public MaterialPoint
{
protected:
    double angle;
    double angular_speed;
    double force_moment;
    double angular_acceleration;
    double inertia_moment;
    Vector2D mass_center;

    Vector2D dr;
    Vector2D dv;

    Vector2D rg;
    Vector2D vg;

public:
    Shape(Vector2D const & r, double angle,
          Vector2D const & v, double angular_speed,
          Vector2D const & f, double force_moment,
          Vector2D const & a, double angular_acceleration,
          double mass, double inertia_moment,
          Vector2D const & mass_center);
    virtual void tick(double dt);
    virtual Vector2D getCoordinates();
    virtual Vector2D getSpeed();
    virtual double getAngle();
    virtual double getAngularSpeed();
    virtual Vector2D getMassCenter();
    virtual Vector2D getMassCenterCoordinates();
    virtual Vector2D getMassCenterSpeed();
};

#endif // SHAPE_H
