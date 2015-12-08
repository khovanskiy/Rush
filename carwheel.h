#ifndef CARWHEEL_H
#define CARWHEEL_H

#include "common/wheel.h"

enum RotationReaction { StraightRot, NoRotation, ReverseRot };

struct CarWheel : public Wheel
{
    bool driving;
    bool braking;
    RotationReaction reaction;
    CarWheel(double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle, Vector2D const & r, double radius,
             bool driving, bool braking, RotationReaction const & reaction);
    CarWheel(CarWheel * carWheel);
    virtual ~CarWheel();
    virtual void changeState(AccelerationState const & acc_state,
                             double rotation);
    virtual double getRotatingSpeed();
    virtual CarWheel* copy();
};

#endif // CARWHEEL_H
