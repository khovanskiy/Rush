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
    int vehicle_type;

    double width;
    double width_with_mirrors;
    double length;
    double height;

    virtual void recalculateMassCenter();
    virtual void setMassCenter(Vector2D mass_center);
    Vehicle(Rectangle2D * shape, double width_with_mirrors, double mass, double inertia_moment, int vehicle_type);
    virtual ~Vehicle();

public:
    static const int DODGE_CHALLENGER_SRT8;
    static const int FERRARI_599GTO;
    static const int FORD_F150_SVT_RAPTOR;

    virtual void setVehicleBody(VehicleBody const & body);
    virtual void setEngine(VehicleEngine const & engine);
    virtual void setWheels(CarTrack back, CarTrack front, double height);
    virtual void addTurret(Turret * turret);
    virtual void setAccelerationState(AccelerationState const & acc_state);
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual int getGear();
    virtual double getImageWidth();
    virtual double getSpins();
    virtual bool isStaying();
    virtual int getVehicleType();
    virtual void invalidate();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    virtual std::vector<Turret*> getTurrets();
    virtual void tick(double dt);
    virtual void postTick(double dt);
};

#endif // VEHICLE_H
