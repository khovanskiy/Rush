#include "carwheel.h"
#include "math.h"
//#include "console.h"

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

CarWheel::CarWheel(CarWheel * carWheel)
    : Wheel(carWheel->mu_parallel_friction, carWheel->mu_parallel_roll,
            carWheel->mu_perpendicular_friction, carWheel->mu_broken_friction,
            carWheel->max_angle, carWheel->r, carWheel->radius)
{
    this->driving = carWheel->driving;
    this->reaction = carWheel->reaction;
}


double CarWheel::getRotatingSpeed()
{
    if (driving)
    {
        return abs(getWheelDirection().scalar(v) / radius);
    }
    else
    {
        return -1;
    }
}


void CarWheel::changeState(AccelerationState const & acc_state,
                           double rotation)
{
    state = Free;
    switch (acc_state)
    {
    case ForwardAcc:
        if (driving)
        {
            state = Forward;            
        }
        break;
    case BackwardAcc:
        if (driving)
        {
            state = Backward;            
        }
        break;
    case Brakes:
        state = Braking;
        break;
    }
    /*switch (state)
    {
    case Forward:
        Console::print("State: Forward");
        break;
    case Backward:
        Console::print("State: Backward");
        break;
    case Free:
        Console::print("State: Free");
        break;
    }*/

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

CarWheel* CarWheel::copy()
{
    return new CarWheel(this);
}
