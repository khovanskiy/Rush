#ifndef TRACK_H
#define TRACK_H
#include "wheel.h"

enum TrackType { LeftTrack, RightTrack };

struct Track : public Wheel
{
    TrackType track_type;

    Track(double mu_parallel_friction, double mu_parallel_roll,
          double mu_perpendicular_friction, double mu_broken_friction,
          double max_angle, Vector2D const & r, double radius,
          TrackType const & track_type);
    Track(Track * track);
    virtual void changeState(AccelerationState const & acc_state,
                             double rotation);
    virtual double getRotatingSpeed();
    virtual Track* copy();
};

#endif // TRACK_H
