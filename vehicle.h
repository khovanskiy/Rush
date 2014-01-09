#ifndef VEHICLE_H
#define VEHICLE_H
#include "physicsobject.h"
#include "chassis.h"
#include "vehiclebody.h"
#include "turret.h"

class Vehicle : public PhysicsObject
{
    friend class PhysicsObjectFactory;

protected:
    Chassis chassis;
    VehicleBody body;
    std::vector<Turret*> turrets;
    AccelerationState acc_state;
    Vector2D mass_center;
    double torque_percent;
    double rotation_percent;
    bool firing_state;
    double firing_angle;
    QString carModel;

    double width;
    double length;
    double height;

    virtual void recalculateMassCenter();
    virtual void setMassCenter(Vector2D mass_center);

public:
    static const QString DODGE_CHALLENGER_SRT8;
    static const QString FERRARI_599GTO;

    Vehicle(Rectangle2D * shape, double mass, double inertia_moment);
    virtual ~Vehicle();
    virtual void setVehicleBody(VehicleBody const & body);
    virtual void setEngine(VehicleEngine const & engine);
    virtual void setWheels(CarTrack back, CarTrack front, double height);
    virtual void addTurret(Turret * turret);
    virtual void setAccelerationState(AccelerationState const & acc_state);
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual int getGear();
    virtual double getSpins();
    virtual bool isStaying();
    virtual QString getCarModel();
    virtual void invalidate();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    virtual std::vector<Turret*> getTurrets();
    virtual void tick(double dt);
};

#endif // VEHICLE_H
