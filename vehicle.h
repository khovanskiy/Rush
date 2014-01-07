#ifndef VEHICLE_H
#define VEHICLE_H
#include "physicsobject.h"
#include "chassis.h"
#include "vehiclebody.h"
#include "turret.h"

class Vehicle : public PhysicsObject
{
    friend class VehicleFactory;

protected:
    Chassis chassis;
    VehicleBody body;
    std::vector<Turret> turrets;
    AccelerationState acc_state;
    Vector2D mass_center;
    double torque_percent;
    bool firing_state;
    double firing_angle;

    double width;
    double length;
    double height;

    virtual std::vector<PhysicsObject*> calculateFireAndForces(double dt);
    virtual void recalculateMassCenter();
    virtual void setMassCenter(Vector2D mass_center);

public:
    double rotation_percent;
    Vehicle(Rectangle2D * shape, double mass, double inertia_moment);
    virtual ~Vehicle();
    virtual void setVehicleBody(VehicleBody const & body);
    virtual void setEngine(VehicleEngine const & engine);
    virtual void setWheels(CarTrack back, CarTrack front, double height);
    virtual void setAccelerationState(AccelerationState const & acc_state);
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual int getGear();
    virtual double getSpins();
    virtual bool isStaying();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
};

#endif // VEHICLE_H
