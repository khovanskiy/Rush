#include "materialpoint.h"

MaterialPoint::MaterialPoint(Vector2D const & r,
                             Vector2D const & v,
                             Vector2D const & f,
                             Vector2D const & a,
                             double mass)
    : r(r), v(v), f(f), a(a)
{
    this->mass = mass;
}

void MaterialPoint::tick(double dt)
{
    r.x += v.x * dt;
    r.y += v.y * dt;
    v.x += a.x * dt;
    v.y += a.y * dt;
    a.x = f.x / mass;
    a.y = f.y / mass;
}

Vector2D MaterialPoint::getCoordinates()
{
    return r;
}

Vector2D MaterialPoint::getSpeed()
{
    return v;
}

double MaterialPoint::getAngle()
{
    return 0;
}

double MaterialPoint::getAngularSpeed()
{
    return 0;
}
