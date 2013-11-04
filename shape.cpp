#include "shape.h"

static const double M_PI = 3.14159265358979323846;

Shape::Shape(Vector2D const & r, double angle,
             Vector2D const & v, double angular_speed,
             Vector2D const & f, double force_moment,
             Vector2D const & a, double angular_acceleration,
             double mass, double inertia_moment,
             Vector2D const & mass_center)
    : MaterialPoint(r, v, f, a, mass), mass_center(mass_center)
{
    this->angle = angle;
    this->angular_speed = angular_speed;
    this->angular_acceleration = angular_acceleration;
    this->force_moment = force_moment;
    this->inertia_moment = inertia_moment;
}

void Shape::tick(double dt)
{
    MaterialPoint::tick(dt);
    angle += angular_speed * dt;
    angular_speed += angular_acceleration * dt;
    angular_acceleration = force_moment / inertia_moment;
    rg = r;
    vg = v;
    dr = mass_center;
    dr.rotate(angle);
    dr.mul(-1);
    dr.add(mass_center);
    rg.add(dr);
    dv = mass_center;
    dv.mul(-1);
    dv.rotate(angle + M_PI / 2);
    dv.mul(angular_speed);
    vg.add(dv);
}

double Shape::getAngle()
{
    return angle;
}

double Shape::getAngularSpeed()
{
    return angular_speed;
}


Vector2D Shape::getCoordinates()
{
    return rg;
}

Vector2D Shape::getSpeed()
{
    return vg;
}
