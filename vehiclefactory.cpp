#include "vehiclefactory.h"

static const double G = 9.80665;
typedef std::vector<RealWheel>::const_iterator wheel_c_it;
typedef std::vector<RealTurret>::const_iterator turret_c_it;

VehicleFactory::VehicleFactory()
{
}

// All vectors r of input body, engine, turrets and wheels
//must be relative to the geometry center of the car.

Vehicle VehicleFactory::createVehicle(Vector2D const & r, double angle,
                                      Vector2D const & v, double angular_speed,
                                      Vector2D const & f, double force_moment,
                                      Vector2D const & a, double angular_acceleration,
                                      double width, double length, double mass_center_height,
                                      RealBody const & r_body,
                                      RealEngine const & r_engine,
                                      std::vector<RealTurret> const & r_turrets,
                                      std::vector<RealWheel> const & r_wheels)
{
    Vector2D mass_center(0, 0);
    double mass = 0;
    Vector2D cur;
    cur = r_body.p.r;
    cur.mul(r_body.p.mass);
    mass_center.add(cur);
    mass += r_body.p.mass;
    cur = r_engine.p.r;
    cur.mul(r_engine.p.mass);
    mass_center.add(cur);
    mass += r_engine.p.mass;
    for (turret_c_it i = r_turrets.cbegin(); i != r_turrets.cend(); i++)
    {
        cur = (*i).p.r;
        cur.mul((*i).p.mass);
        mass_center.add(cur);
        mass += (*i).p.mass;
    }
    for (wheel_c_it i = r_wheels.cbegin(); i != r_wheels.cend(); i++)
    {
        cur = (*i).p.r;
        cur.mul((*i).p.mass);
        mass_center.add(cur);
        mass += (*i).p.mass;
    }
    mass_center.div(mass);
    double inertia_moment = r_body.p.mass * (width * width + length * length) / 12;
    double len;
    VehicleBody body(r_body.body);
    body.r = r_body.p.r;
    body.r.sub(mass_center);
    Vector2D pos = r_engine.p.r;
    pos.sub(mass_center);
    len = pos.getLength();
    inertia_moment += len * len * r_engine.p.mass;
    pos = r_body.p.r;
    pos.sub(mass_center);
    len = pos.getLength();
    inertia_moment += len * len * r_body.p.mass;
    std::vector<Wheel*> wheels = std::vector<Wheel*>();
    for (wheel_c_it i = r_wheels.cbegin(); i != r_wheels.cend(); i++)
    {
        Wheel * wheel = (*i).wheel->copy();
        wheel->r.sub(mass_center);
        len = wheel->r.getLength();
        inertia_moment += len * len * (*i).p.mass;
        wheels.push_back(wheel);
    }
    std::vector<Turret> turrets = std::vector<Turret>();
    for (turret_c_it i = r_turrets.cbegin(); i != r_turrets.cend(); i++)
    {
        Turret turret((*i).turret);
        turret.r.sub(mass_center);
        len = turret.r.getLength();
        inertia_moment += len * len * (*i).p.mass;
        turrets.push_back(turret);
    }
    Chassis chassis(wheels, r_engine.engine, mass * G, mass_center, mass_center_height);
    return Vehicle(r, angle, v, angular_speed, f, force_moment, a,
                   angular_acceleration, mass, width, length, mass_center, inertia_moment,
                   body, chassis, turrets);
}
