#ifndef CARWHEEL_H
#define CARWHEEL_H
#include "physicswheel.h"

enum RotationReaction { StraightRot, NoRotation, ReverseRot };

struct CarWheel : public PhysicsWheel
{
    bool driving;
    RotationReaction reaction;
    CarWheel(double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle, Vector2D r, double radius,
             bool driving, RotationReaction reaction);
    virtual void changeState(AccelerationState acc_state,
                             double rotation);
};

#endif // CARWHEEL_H
