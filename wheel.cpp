#include "wheel.h"
#include "console.h"
#include <QVariant>
static const double M_PI = 3.14159265358979323846;
static const double G = 9.80665;
static const double eps = 1e-9;
static const double shaking_koef = 0.5;
static const double default_surface_friction = 2.5;

#include <math.h>

Wheel::Wheel(double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle, Vector2D const & r, double radius)
    : r(r)
{
    this->mu_parallel_friction = mu_parallel_friction;
    this->mu_parallel_roll = mu_parallel_roll;
    this->mu_perpendicular_friction = mu_perpendicular_friction;
    this->mu_broken_friction = mu_broken_friction;
    this->max_angle = max_angle;
    this->radius = radius;
    this->surface_friction = default_surface_friction;
}

void Wheel::setWheelAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

Vector2D Wheel::getWheelDirection()
{
    return Vector2D(-sin(angle), cos(angle));
}

double Wheel::getChangedMu(double mu)
{
    return mu * surface_friction;
}

double Wheel::getMaxAccelerationTorque()
{
    if ((state == WheelState::Forward) || (state == WheelState::Backward)) {
        /*Console::print("Calculating max acc torque:");
        Console::print("Distributed weigth:");
        Console::print(distributed_weight);
        Console::print("Mu:");
        Console::print(getChangedMu(mu_parallel_friction));
        Console::print("Radius:");
        Console::print(radius);
        Console::print("Total torque:");
        Console::print(distributed_weight * getChangedMu(mu_parallel_friction) * radius);/**/
        return distributed_weight * getChangedMu(mu_parallel_friction) * radius;
    }
    else
    {
        return 0;
    }
}

void Wheel::setTorque(double percent)
{
    distributed_torque = getMaxAccelerationTorque() * percent;
}

void Wheel::calculateForces(double dt)
{
    f = Vector2D(0, 0);
    double mu_par, mu_perp;
    switch (state)
    {
    case WheelState::Broken:
        mu_par = mu_broken_friction;
        mu_perp = mu_broken_friction;
        break;
    case WheelState::Braking:
        mu_par = mu_parallel_friction;
        mu_perp = mu_perpendicular_friction;
        break;
    case WheelState::Free:        
    case WheelState::Forward:
    case WheelState::Backward:
    default:
        mu_par = mu_parallel_roll / radius;
        mu_perp = mu_perpendicular_friction;
        break;
    }
    double vl = v.getLength();
    Vector2D w = getWheelDirection();
    double alpha = Vector2D::angleBetween(w, v);
    double v_par = abs(v.scalar(w));
    double v_perp = sqrt(abs(vl * vl - v_par * v_par));
    if (v_par > eps) {
        Vector2D f_par = w;
        if (f_par.scalar(v) > 0)
        {
            f_par.mul(-1);
        }
        f_par.mul(distributed_weight * getChangedMu(mu_par) * cos(alpha) * cos(alpha));
        if (f_par.getLength() > shaking_koef * v_par * (distributed_weight / G) / dt)
        {
            f_par.setLength(shaking_koef * v_par * (distributed_weight / G) / dt);
        }
        f.add(f_par);
    }
    if (v_perp > eps) {
        Vector2D f_perp = w;
        f_perp.rotate(M_PI / 2);
        if (f_perp.scalar(v) > 0)
        {
            f_perp.mul(-1);
        }
        f_perp.mul(distributed_weight * getChangedMu(mu_perp));
        if (f_perp.getLength() > shaking_koef * v_perp * (distributed_weight / G) / dt)
        {
            f_perp.setLength(shaking_koef * v_perp * (distributed_weight / G) / dt);
        }
        f.add(f_perp);
    }
    if ((state == WheelState::Forward) || (state == WheelState::Backward))
    {
        int force_koef = (state == WheelState::Forward ? 1 : -1);
        Vector2D acc_force = w;
        acc_force.mul((force_koef * distributed_torque / radius));
        f.add(acc_force);
    }
    force_moment = r.cross(f);
}


