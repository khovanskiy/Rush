#ifndef PHYSICSVEHICLE_H
#define PHYSICSVEHICLE_H
#include "box.h"
#include "chassis.h"
#include "realbody.h"
#include "realengine.h"
#include "realturret.h"
#include "realwheel.h"

class Vehicle : public Box
{
protected:
    VehicleBody body;
    Chassis chassis;
    std::vector<Turret> turrets;
    AccelerationState acc_state;
    double torque_percent;
    bool firing_state;
    double firing_angle;

    virtual void calculateFireAndForces(double dt);

public:
    double rotation_percent;
    Vehicle(Vector2D const & r, double angle,
            Vector2D const & v, double angular_speed,
            Vector2D const & f, double force_moment,
            Vector2D const & a, double angular_acceleration,
            double mass, double width, double length,
            Vector2D const & mass_center, double inertia_moment,
            VehicleBody const & body, Chassis const & chassis,
            std::vector<Turret> const & turrets);
    ~Vehicle();
    virtual void setAccelerationState(AccelerationState acc_state);
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual void tick(double dt);
    virtual int getGear();
    virtual double getSpins();
    virtual bool isStaying();
};

#endif // PHYSICSVEHICLE_H
