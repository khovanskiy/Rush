#include "vehiclefactory.h"

static const double G = 9.80665;

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
                                      RealBody r_body,
                                      RealEngine r_engine,
                                      std::vector<RealTurret> r_turrets,
                                      std::vector<RealWheel> r_wheels)
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
    for (std::vector<RealTurret>::iterator i = r_turrets.begin(); i != r_turrets.end(); i++)
    {
        cur = (*i).p.r;
        cur.mul((*i).p.mass);
        mass_center.add(cur);
        mass += (*i).p.mass;
    }
    for (std::vector<RealWheel>::iterator i = r_wheels.begin(); i != r_wheels.end(); i++)
    {
        cur = (*i).p.r;
        cur.mul((*i).p.mass);
        mass_center.add(cur);
        mass += (*i).p.mass;
    }
    mass_center.div(mass);
    double inertia_moment = r_body.p.mass * (width * width + length * length) / 12;
    double len;
    r_body.p.r.sub(mass_center);
    r_body.body.r = r_body.p.r;
    len = r_body.p.r.getLength();
    inertia_moment += len * len * r_body.p.mass;
    std::vector<Wheel*> wheels;
    for (std::vector<RealWheel>::iterator i = r_wheels.begin(); i != r_wheels.end(); i++)
    {
        (*i).p.r.sub(mass_center);
        (*i).wheel->r = (*i).p.r;
        len = (*i).p.r.getLength();
        inertia_moment += len * len * (*i).p.mass;
        wheels.push_back((*i).wheel);
    }
    std::vector<Turret> turrets;
    for (std::vector<RealTurret>::iterator i = r_turrets.begin(); i != r_turrets.end(); i++)
    {
        (*i).p.r.sub(mass_center);
        (*i).turret.r = (*i).p.r;
        len = (*i).p.r.getLength();
        inertia_moment += len * len * (*i).p.mass;
        turrets.push_back((*i).turret);
    }
    Chassis chassis(wheels, r_engine.engine, mass * G, mass_center, mass_center_height);
    return Vehicle(r, angle, v, angular_speed, f, force_moment, a,
                   angular_acceleration, mass, width, length, mass_center, inertia_moment,
                   r_body.body, chassis, turrets);
}
