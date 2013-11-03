#ifndef TRACK_H
#define TRACK_H
#include "physicswheel.h"

enum TrackType { LeftTrack, RightTrack };

struct Track : public PhysicsWheel
{
    TrackType track_type;

    Track(double mu_parallel_friction, double mu_parallel_roll,
          double mu_perpendicular_friction, double mu_broken_friction,
          double max_angle, Vector2D r, double radius,
          TrackType track_type);
    virtual void changeState(AccelerationState acc_state,
                             double rotation);
};

#endif // TRACK_H
