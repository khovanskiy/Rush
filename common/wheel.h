#ifndef PHYSICSWHEEL_H
#define PHYSICSWHEEL_H
#include "vector2d.h"
#include "WheelState.h"
#include "AccelerationState.h"

struct Wheel
{
    double mu_parallel_friction, mu_parallel_roll;
    double mu_perpendicular_friction, mu_broken_friction;
    double max_angle;
    Vector2D r;
    double radius;

    WheelState state;
    double angle;
    Vector2D v;
    double distributed_weight;
    double distributed_torque;
    double surface_friction;
    Vector2D f;
    double force_moment;

    Wheel(double mu_parallel_friction, double mu_parallel_roll,
                 double mu_perpendicular_friction, double mu_broken_friction,
                 double max_angle, Vector2D const & r, double radius);
    virtual ~Wheel();
    void setWheelAngle(double percent);
    void calculateForces(double dt);
    Vector2D getWheelDirection();
    double getChangedMu(double mu);
    double getMaxAccelerationTorque();
    void setTorque(double percent);
    virtual void changeState(AccelerationState const & acc_state,
                             double rotation) = 0;
    virtual double getRotatingSpeed() = 0;
    virtual Wheel* copy() = 0;

};

#endif // PHYSICSWHEEL_H
