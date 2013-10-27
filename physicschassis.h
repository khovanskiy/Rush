#ifndef PHYSICSCHASSIS_H
#define PHYSICSCHASSIS_H
#include "physicswheel.h"
#include "physicsvehicleengine.h"
#include "vector2d.h"

struct PhysicsChassis
{
    enum WheelType
    {
        DrivingRotating,
        DrivingReverseRotating,
        NonDrivingRotating,
        NonDrivingReverseRotating,
        DrivingNonRotating,
        NonDrivingNonRotating,
        LeftTrack,
        RightTrack
    };

    std::vector<PhysicsWheel> wheels;
    PhysicsVehicleEngine engine;
    double weight;
    double height;

    Vector2D v;
    Vector2D a;
    Vector2D f;
    double angular_speed;
    double angular_acceleration;
    double force_moment;

    PhysicsChassis(std::vector<PhysicsWheel> wheels, PhysicsVehicleEngine engine);
    void turningLeft();
};

#endif // PHYSICSCHASSIS_H
