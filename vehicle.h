#ifndef PHYSICSVEHICLE_H
#define PHYSICSVEHICLE_H
#include "box.h"
#include "chassis.h"
#include "vehiclebody.h"
#include "turret.h"

struct Position
{
    Vector2D r;
    double mass;

    Position(Vector2D const & r, double mass)
    {
        this->r = r;
        this->mass = mass;
    }
    Position(Position const & p)
    {
        this->r = p.r;
        this->mass = p.mass;
    }
};

struct RealBody
{
    Position p;
    VehicleBody body;

    RealBody(Position const & p, VehicleBody const & body)
        : p(p), body(body)
    {
    }
};

struct RealEngine
{
    Position p;
    VehicleEngine engine;

    RealEngine(Position const & p, VehicleEngine const & engine)
        : p(p), engine(engine)
    {
    }
};

struct RealTurret
{
    Position p;
    Turret turret;

    RealTurret(Position const & p, Turret const & turret)
        : p(p), turret(turret)
    {
    }
};

struct RealWheel
{
    Position p;
    Wheel * wheel;

    RealWheel(Position const & p, Wheel * wheel)
        : p(p)
    {
        this->wheel = wheel;
    }
};

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
