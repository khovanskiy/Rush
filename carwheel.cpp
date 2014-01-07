#include "carwheel.h"
#include "math.h"
#include "console.h"

CarWheel::CarWheel(double mu_parallel_friction, double mu_parallel_roll,
                   double mu_perpendicular_friction, double mu_broken_friction,
                   double max_angle, Vector2D const & r, double radius,
                   bool driving, bool braking, RotationReaction const & reaction)
    : Wheel(mu_parallel_friction, mu_parallel_roll,
            mu_perpendicular_friction, mu_broken_friction,
            max_angle, r, radius)
{
    /*Console::print("Car wheel created:");
    Console::print("Radius:");
    Console::print(radius);
    Console::print("Coordinates:");
    Console::print(r);
            /**/
    this->driving = driving;
    this->braking = braking;
    this->reaction = reaction;
}

CarWheel::CarWheel(CarWheel * carWheel)
    : Wheel(carWheel->mu_parallel_friction, carWheel->mu_parallel_roll,
            carWheel->mu_perpendicular_friction, carWheel->mu_broken_friction,
            carWheel->max_angle, carWheel->r, carWheel->radius)
{
    this->driving = carWheel->driving;
    this->braking = carWheel->braking;
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
    state = WheelState::Free;
    switch (acc_state)
    {
    case AccelerationState::ForwardAcc:
        if (driving)
        {
            state = WheelState::Forward;
        }
        break;
    case AccelerationState::BackwardAcc:
        if (driving)
        {
            state = WheelState::Backward;
        }
        break;
    case AccelerationState::Brakes:
        if (braking)
        {
            state = WheelState::Braking;
        }
        break;
    }   
    double percent = 0;
    if (reaction == RotationReaction::StraightRot)
    {
        percent = rotation;
    }
    else if (reaction == RotationReaction::ReverseRot)
    {
        percent = -rotation;
    }
    this->setWheelAngle(percent);
}

CarWheel* CarWheel::copy()
{
    return new CarWheel(this);
}
