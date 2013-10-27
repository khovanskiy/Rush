#include "physicswheel.h"
#define M_PI	 3.14159265358979323846
#include <math.h>

PhysicsWheel::PhysicsWheel(bool driving,
                           double mu_parallel_friction, double mu_parallel_roll,
                           double mu_perpendicular_friction, double mu_broken_friction,
                           double max_angle, Vector2D r, double radius)
{
    this->driving = driving;
    this->mu_parallel_friction = mu_parallel_friction;
    this->mu_parallel_roll = mu_parallel_roll;
    this->mu_perpendicular_friction = mu_perpendicular_friction;
    this->mu_broken_friction = mu_broken_friction;
    this->max_angle = max_angle;
    this->r = r;
    this->radius = radius;
    this->surface_friction = 1;
}

void PhysicsWheel::setDistributedWeight(double distributed_weight)
{
    this->distributed_weight = distributed_weight;
}

void PhysicsWheel::setDistributedTorque(double distributed_torque)
{
    this->distributed_torque = distributed_torque;
}

void PhysicsWheel::setSpeed(Vector2D v)
{
    this->v = v;
}

void PhysicsWheel::setWheelAngle(double percent)
{
    this->angle = this->max_angle * percent;
}

void PhysicsWheel::setWheelState(WheelState state)
{
    this->state = state;
}

void PhysicsWheel::setSurfaceFriction(double surface_friction)
{
    this->surface_friction = surface_friction;
}

void PhysicsWheel::calculateForces(double dt)
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

Vector2D PhysicsWheel::getWheelDirection()
{
    return Vector2D(-sin(angle), cos(angle));
}

double PhysicsWheel::getRotatingSpeed()
{
    return getWheelDirection().scalar(v) / radius;
}

double PhysicsWheel::getChangedMu(double mu)
{
    return mu * surface_friction;
}

double PhysicsWheel::getMaxAccelerationTorque()
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
