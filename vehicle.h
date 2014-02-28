#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>

#include "gamemodelobject.h"
#include "physicsobject.h"
#include "chassis.h"
#include "vehiclebody.h"
#include "turret.h"


class Vehicle : public PhysicsObject
{
    friend class PhysicsObjectFactory;

public:
    Vehicle(Rectangle2D * shape, int mass);

    virtual ~Vehicle();

    virtual void tick(double dt);

    static const int DODGE_CHALLENGER_SRT8;
    static const int FERRARI_599GTO;
    static const int FORD_F150_SVT_RAPTOR;

    virtual void setVehicleBody(VehicleBody const & body);
    virtual void setEngine(VehicleEngine const & engine);
    virtual void setWheels(CarTrack back, CarTrack front, double height);
    virtual void addTurret(Turret* turret);

    virtual void setAccelerationState(AccelerationState const & acc_state);
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual void turretsToPoint(const Vector2D& target);

    virtual int getGear();
    virtual double getSpins();
    virtual bool isStaying();
    virtual int getVehicleType();

    virtual std::vector<PhysicsObject*>* calculateInnerState(double dt);
    virtual std::vector<Turret*> getTurrets();

    Chassis chassis;
    VehicleBody body;
    std::vector<Turret*> turrets;
    AccelerationState acc_state;

    Vector2D mass_center;
    double torque_percent;
    double rotation_percent;
    bool firing_state;
    double firing_angle;
    int vehicle_type;

    double width;
    double length;
    double height;

    virtual void recalculateMassCenter();
    virtual void setMassCenter(Vector2D mass_center);
};

#endif // VEHICLE_H
