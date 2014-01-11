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
    bool firing_state;
    double firing_angle;
    QString vehicle_type;

    double width;
    double length;
    double height;

    virtual void recalculateMassCenter();
    virtual void setMassCenter(Vector2D mass_center);
    Vehicle(Rectangle2D * shape, double mass, double inertia_moment, QString vehicle_type);
    virtual ~Vehicle();

public:
<<<<<<< HEAD
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
=======
    static const QString DODGE_CHALLENGER_SRT8;
    static const QString FERRARI_599GTO;

    virtual void setVehicleBody(VehicleBody const & body);
    virtual void setEngine(VehicleEngine const & engine);
    virtual void setWheels(CarTrack back, CarTrack front, double height);
    virtual void addTurret(Turret * turret);
    virtual void setAccelerationState(AccelerationState const & acc_state);
>>>>>>> origin/physicsDebug
    virtual void setTorquePercent(double torque_percent);
    virtual void setRotationPercent(double rotation_percent);
    virtual void setFiring(bool firing_state, double firing_angle);
    virtual int getGear();
    virtual double getSpins();
    virtual bool isStaying();
<<<<<<< HEAD
=======
    virtual QString getVehicleType();
    virtual void invalidate();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    virtual std::vector<Turret*> getTurrets();
    virtual void tick(double dt);
    virtual void postTick(double dt);
>>>>>>> origin/physicsDebug
};

#endif // VEHICLE_H
