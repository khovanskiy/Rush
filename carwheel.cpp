#include "carwheel.h"

CarWheel::CarWheel(double mu_parallel_friction, double mu_parallel_roll,
                   double mu_perpendicular_friction, double mu_broken_friction,
                   double max_angle, Vector2D const & r, double radius,
                   bool driving, RotationReaction const & reaction)
    : Wheel(mu_parallel_friction, mu_parallel_roll,
                   mu_perpendicular_friction, mu_broken_friction,
                   max_angle, r, radius)
{
    this->driving = driving;
    this->reaction = reaction;
}

void CarWheel::changeState(AccelerationState const & acc_state,
                           double rotation)
{
    switch (acc_state)
    {
    case ForwardAcc:
        if (driving)
        {
            state = Forward;
        }
        else
        {
            state = Free;
        }
        break;
    case BackwardAcc:
        if (driving)
        {
            state = Backward;
        }
        else
        {
            state = Free;
        }
        break;
    case NoAcc:
        state = Free;
        break;
    case Brakes:
        state = Braking;
        break;
    }
    double percent = 0;
    if (reaction == StraightRot)
    {
        percent = rotation;
    }
    else if (reaction == ReverseRot)
    {
        percent = -rotation;
    }
    this->setWheelAngle(percent);
}
