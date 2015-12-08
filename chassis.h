#ifndef PHYSICSCHASSIS_H
#define PHYSICSCHASSIS_H

#include "carwheel.h"
#include "vehicleengine.h"
#include "vector2d.h"
#include "common/wheel.h"

struct CarTrack {
    double y;
    double width;
    double wheel_radius;
    bool driving;
    bool braking;
    RotationReaction reaction;
    double weigth_percent;
    double mu_parallel_friction;
    double mu_parallel_roll;
    double mu_perpendicular_friction;
    double mu_broken_friction;
    double max_angle;

    CarTrack(double y, double width, double wheel_radius, double weight_percent,
             bool driving, bool braking, RotationReaction reaction,
             double mu_parallel_friction, double mu_parallel_roll,
             double mu_perpendicular_friction, double mu_broken_friction,
             double max_angle) {
        this->y = y;
        this->width = width;
        this->wheel_radius = wheel_radius;
        this->weigth_percent = weight_percent;
        this->driving = driving;
        this->braking = braking;
        this->reaction = reaction;
        this->mu_parallel_friction = mu_parallel_friction;
        this->mu_parallel_roll = mu_parallel_roll;
        this->mu_perpendicular_friction = mu_perpendicular_friction;
        this->mu_broken_friction = mu_broken_friction;
        this->max_angle = max_angle;
    }
};

class Chassis {
protected:
    void distributeWeigth();

    void setWheelsReaction();

    void setWheelsSpeed();

    void distributeTorque();

    void sumForces(double dt);

public:
    std::vector<Wheel *> wheels;
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


    Vector2D f;
    double force_moment;

    Chassis();

    Chassis(Chassis const &chassis);

    ~Chassis();

    void setWheels(double mass, double height,
                   CarTrack back, CarTrack front);

    void setEngine(VehicleEngine const &engine);

    void setStructure(double mass, Vector2D const &mass_center, double height);

    void setTotalState(Vector2D const &v, Vector2D const &a, double angular_speed,
                       double torque_percent, AccelerationState const &acc_state,
                       double rotation);

    void calculateForces(double dt);

    int getGear();

    double getSpins();

    Vector2D getMassCenter();
};

#endif // PHYSICSCHASSIS_H
