#include "track.h"
#include "math.h"

Track::Track(double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle, Vector2D const & r, double radius,
             TrackType const & track_type)
    : Wheel(mu_parallel_friction, mu_parallel_roll,
            mu_perpendicular_friction, mu_broken_friction,
            max_angle, r, radius)
{
    this->track_type = track_type;
}

Track::Track(Track * track)
    : Wheel(track->mu_parallel_friction, track->mu_parallel_roll,
            track->mu_perpendicular_friction, track->mu_broken_friction,
            track->max_angle, track->r, track->radius)
{
    this->track_type = track->track_type;
}


double Track::getRotatingSpeed()
{
    return abs(getWheelDirection().scalar(v) / radius);
}


void Track::changeState(AccelerationState const & acc_state,
                        double rotation)
{
    if (track_type == TrackType::LeftTrack)
    {
        switch (acc_state)
        {
        case AccelerationState::ForwardAcc:
            if (rotation > 0)
            {
                this->state = WheelState::Free;
            }
            else
            {
                this->state = WheelState::Forward;
            }
            break;
        case AccelerationState::NoAcc:
            if (rotation > 0)
            {
                this->state = WheelState::Backward;
            }
            else if (rotation < 0)
            {
                this->state = WheelState::Forward;
            }
            else
            {
                this->state = WheelState::Free;
            }
            break;
        case AccelerationState::BackwardAcc:
            if (rotation > 0)
            {
                this->state = WheelState::Free;
            }
            else
            {
                this->state = WheelState::Backward;
            }
            break;
        case AccelerationState::Brakes:
            this->state = WheelState::Braking;
            break;
        }
    }
    else if (track_type == TrackType::RightTrack)
    {
        switch (acc_state)
        {
        case AccelerationState::ForwardAcc:
            if (rotation < 0)
            {
                this->state = WheelState::Free;
            }
            else
            {
                this->state = WheelState::Forward;
            }
            break;
        case AccelerationState::NoAcc:
            if (rotation < 0)
            {
                this->state = WheelState::Backward;
            }
            else if (rotation > 0)
            {
                this->state = WheelState::Forward;
            }
            else
            {
                this->state = WheelState::Free;
            }
            break;
        case AccelerationState::BackwardAcc:
            if (rotation < 0)
            {
                this->state = WheelState::Free;
            }
            else
            {
                this->state = WheelState::Backward;
            }
            break;
        case AccelerationState::Brakes:
            this->state = WheelState::Braking;
            break;
        }
    }
}

Track* Track::copy()
{
    return new Track(this);
}
