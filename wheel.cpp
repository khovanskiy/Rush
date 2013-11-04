#include "wheel.h"
static const double M_PI = 3.14159265358979323846;
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
    this->surface_friction = 1;
}

void Wheel::setWheelAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

Vector2D Wheel::getWheelDirection()
{
    return Vector2D(-sin(angle), cos(angle));
}

double Wheel::getRotatingSpeed()
{
    return abs(getWheelDirection().scalar(v) / radius);
}

double Wheel::getChangedMu(double mu)
{
    return mu * surface_friction;
}

double Wheel::getMaxAccelerationTorque()
{
    if ((state == Forward) || (state == Backward)) {
        double alpha = Vector2D::angleBetween(getWheelDirection(), v);
        return distributed_weight * cos(alpha) * cos(alpha) * getChangedMu(mu_parallel_friction) * radius;
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
    double vl;
    double mu_par = 0, mu_perp = 0;
    switch (state)
    {
    case Broken:
    case Braking:
    case Free:
        switch (state)
        {
        case Broken:
            mu_par = mu_broken_friction;
            mu_perp = mu_broken_friction;
            break;
        case Braking:
            mu_par = mu_parallel_friction;
            mu_perp = mu_perpendicular_friction;
            break;
        case Free:
            mu_par = mu_parallel_roll;
            mu_perp = mu_perpendicular_friction;
            break;
        }
        vl = v.getLength();
        if (vl > 0)
        {
            Vector2D w = getWheelDirection();
            double alpha = Vector2D::angleBetween(w, v);
            double mu = getChangedMu(mu_par * cos(alpha) * cos(alpha)
                                     + mu_perp * sin(alpha) * sin(alpha));
            f = v;
            if (distributed_weight * mu > vl / dt) {
                f.setLength(-vl / dt);
            }
            else
            {
                f.setLength(-distributed_weight * mu);
            }
        }
        else
        {
            f.mul(0);
        }
        break;
    case Forward:
    case Backward:
        int force_koef = (state == Forward ? 1 : -1);
        Vector2D w = getWheelDirection();
        Vector2D acc_force = w;
        acc_force.mul((force_koef * distributed_torque / radius));
        Vector2D par_roll_friction = w;
        par_roll_friction.setLength(distributed_weight * getChangedMu(mu_parallel_roll));
        if (v.scalar(par_roll_friction) > 0)
        {
            par_roll_friction.mul(-1);
        }
        acc_force.add(par_roll_friction);
        vl = v.getLength();
        if (vl > 0)
        {
            Vector2D perp_friction = w;
            perp_friction.rotate(M_PI / 2);
            Vector2D v_perp = perp_friction;
            v_perp.mul(v.scalar(perp_friction));
            perp_friction.setLength(distributed_weight * sin(Vector2D::angleBetween(v, w))
                                    * getChangedMu(mu_perpendicular_friction));
            if (v.scalar(perp_friction) > 0) {
                perp_friction.mul(-1);
            }
            if (perp_friction.getLength() * dt > v_perp.getLength())
            {
                perp_friction.setLength(v_perp.getLength() / dt);
            }
            Vector2D forces_sum = perp_friction;
            forces_sum.add(acc_force);
            acc_force.mul(acc_force.getLength() / forces_sum.getLength());
            perp_friction.mul(perp_friction.getLength() / forces_sum.getLength());
            f = acc_force;
            f.add(perp_friction);
        }
        else
        {
            f = acc_force;
        }
        break;
    }
    force_moment = r.cross(f);
}


