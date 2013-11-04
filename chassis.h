#ifndef PHYSICSCHASSIS_H
#define PHYSICSCHASSIS_H
#include "wheel.h"
#include "vehicleengine.h"
#include "vector2d.h"

class Chassis
{
    std::vector<Wheel*> wheels;
    VehicleEngine engine;
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

    void setTotalState(Vector2D const & v, Vector2D const & a, double angular_speed,
                       double torque_percent, AccelerationState const & acc_state,
                       double rotation);
    void calculateForces(double dt);
    Chassis(std::vector<Wheel*> const & wheels, VehicleEngine const & engine,
                   double weight, Vector2D const & mass_center, double height);
};

#endif // PHYSICSCHASSIS_H
