#include "track.h"

Track::Track(double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle, Vector2D r, double radius,
             TrackType track_type)
: PhysicsWheel(mu_parallel_friction, mu_parallel_roll,
             mu_perpendicular_friction, mu_broken_friction,
             max_angle, r, radius)
{
    this->track_type = track_type;
}

void Track::changeState(AccelerationState acc_state,
                        double rotation)
{
    if (track_type == LeftTrack)
    {
        switch (acc_state)
        {
        case ForwardAcc:
            if (rotation > 0)
            {
                this->state = Free;
            }
            else
            {
                this->state = Forward;
            }
            break;
        case NoAcc:
            if (rotation > 0)
            {
                this->state = Backward;
            }
            else if (rotation < 0)
            {
                this->state = Forward;
            }
            else
            {
                this->state = Free;
            }
            break;
        case BackwardAcc:
            if (rotation > 0)
            {
                this->state = Free;
            }
            else
            {
                this->state = Backward;
            }
            break;
        case Brakes:
            this->state = Braking;
            break;
        }
    }
    else
    {
        switch (acc_state)
        {
        case ForwardAcc:
            if (rotation < 0)
            {
                this->state = Free;
            }
            else
            {
                this->state = Forward;
            }
            break;
        case NoAcc:
            if (rotation < 0)
            {
                this->state = Backward;
            }
            else if (rotation > 0)
            {
                this->state = Forward;
            }
            else
            {
                this->state = Free;
            }
            break;
        case BackwardAcc:
            if (rotation < 0)
            {
                this->state = Free;
            }
            else
            {
                this->state = Backward;
            }
            break;
        case Brakes:
            this->state = Braking;
            break;
        }
    }
}
