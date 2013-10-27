#ifndef PHYSICSWHEEL_H
#define PHYSICSWHEEL_H
#include "vector2d.h"

struct PhysicsWheel
{
    enum WheelState { Broken, Braking, Free, Forward, Backward };

    //Constants for this wheel.
    //Vector r is relative to the mass center of vehicle.

    double mu_parallel_friction, mu_parallel_roll;
    double mu_perpendicular_friction, mu_broken_friction;
    double max_angle;
    Vector2D r;
    double radius;

    //Current state of this wheel.

    WheelState state;
    double angle;
    Vector2D v;
    double distributed_weight;
    double distributed_torque;
    double surface_friction;
    Vector2D f;
    double force_moment;

    PhysicsWheel(double mu_parallel_friction, double mu_parallel_roll,
                 double mu_perpendicular_friction, double mu_broken_friction,
                 double max_angle, Vector2D r, double radius);

    void setWheelAngle(double percent);
    void setWheelState(WheelState state);
    void setDistributedWeight(double distributed_weight);
    void setDistributedTorque(double distributed_torque);
    void setSpeed(Vector2D v);
    void setSurfaceFriction(double surface_friction);
    void calculateForces(double dt);
    Vector2D getWheelDirection();
    double getRotatingSpeed();
    double getChangedMu(double mu);
    double getMaxAccelerationTorque();
};

#endif // PHYSICSWHEEL_H
