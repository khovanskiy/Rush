#ifndef PHYSICSCHASSIS_H
#define PHYSICSCHASSIS_H
#include "physicswheel.h"
#include "physicsvehicleengine.h"
#include "vector2d.h"

class PhysicsChassis
{
    std::vector<PhysicsWheel*> wheels;
    PhysicsVehicleEngine engine;
    double weight;
    Vector2D mass_center;
    double height;

    Vector2D v;
    Vector2D a;
    double angular_speed;
    double torque_percent;
    AccelerationState acc_state;
    double rotation;

    void distributeWeigth();
    void setWheelsReaction();
    void setWheelsSpeed();
    void distributeTorque();
    void sumForces(double dt);

public:
    Vector2D f;
    double force_moment;

    void setTotalState(Vector2D v, Vector2D a, double angular_speed,
                       double torque_percent, AccelerationState acc_state,
                       double rotation);
    void calculateForces(double dt);
    PhysicsChassis(std::vector<PhysicsWheel*> wheels, PhysicsVehicleEngine engine,
                   double weight, Vector2D mass_center, double height);
};

#endif // PHYSICSCHASSIS_H
