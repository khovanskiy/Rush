#include "vehiclefactory.h"

static const double G = 9.80665;
static const double M_PI = 3.14159265358979323846;
static const double inch_to_meter = 0.0254;
static const double straight_air_koef = 1;
static const double back_air_koef = 3;
static const double left_air_koef = 5;
static const double right_air_koef = 5;
static const double rotation_air_koef = 100;
typedef std::vector<RealWheel>::const_iterator wheel_c_it;
typedef std::vector<RealTurret>::const_iterator turret_c_it;

VehicleFactory::VehicleFactory()
{
}

Vehicle * VehicleFactory::createVehicle(Vector2D const & r, double angle,
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
        cur = i->p.r;
        cur.mul(i->p.mass);
        mass_center.add(cur);
        mass += i->p.mass;
    }
    for (wheel_c_it i = r_wheels.cbegin(); i != r_wheels.cend(); i++)
    {
        cur = i->p.r;
        cur.mul(i->p.mass);
        mass_center.add(cur);
        mass += i->p.mass;
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
    return new Vehicle(r, angle, v, angular_speed, f, force_moment, a,
                   angular_acceleration, mass, width, length, mass_center, inertia_moment,
                   body, chassis, turrets);
}

double VehicleFactory::revsPerKmToRadius(double revsPerKilometer)
{
    return 1000 / (2 * M_PI * revsPerKilometer);
}

double VehicleFactory::tireSpecsToRadius(double tread_width,
                                         double aspect_ratio, double rim_diameter)
{
    return ((tread_width / 1000) * (aspect_ratio / 100) + rim_diameter * inch_to_meter);
}


Vehicle * VehicleFactory::createCar(Vector2D const & r, double angle,
                         Vector2D const & v, double angular_speed,
                         double length, double width, double mass, double height,
                         double mu_parallel_friction, double mu_parallel_roll,
                         double mu_perpendicular_friction, double mu_broken_friction,
                         double max_angle,
                         CarTrack back, CarTrack front,
                         double air_resistance_koef,
                         double max_engine_torque,
                         double max_engine_spins_per_minute,
                         std::vector<double> gear_ratios,
                         double final_ratio,
                         std::vector<RealTurret> turrets)
{
    std::vector<RealWheel> r_wheels;
    r_wheels.push_back(RealWheel(Position(Vector2D(-front.width/2, front.y), 0),
                               new CarWheel(mu_parallel_friction, mu_parallel_roll,
                                  mu_perpendicular_friction, mu_broken_friction,
                                  max_angle, Vector2D(-front.width/2, front.y),
                                  front.wheel_radius, front.driving, front.reaction)));
    r_wheels.push_back(RealWheel(Position(Vector2D(front.width/2, front.y), 0),
                               new CarWheel(mu_parallel_friction, mu_parallel_roll,
                                  mu_perpendicular_friction, mu_broken_friction,
                                  max_angle, Vector2D(front.width/2, front.y),
                                  front.wheel_radius, front.driving, front.reaction)));
    r_wheels.push_back(RealWheel(Position(Vector2D(-back.width/2, back.y), 0),
                               new CarWheel(mu_parallel_friction, mu_parallel_roll,
                                  mu_perpendicular_friction, mu_broken_friction,
                                  max_angle, Vector2D(-back.width/2, back.y),
                                  back.wheel_radius, back.driving, back.reaction)));
    r_wheels.push_back(RealWheel(Position(Vector2D(back.width, back.reaction), 0),
                               new CarWheel(mu_parallel_friction, mu_parallel_roll,
                                  mu_perpendicular_friction, mu_broken_friction,
                                  max_angle, Vector2D(back.width/2, back.y),
                                  back.wheel_radius, back.driving, back.reaction)));
    double mass_center_height = height / 6;
    std::vector<VehicleEngine::Gear> gears;
    int n = 0;
    for (std::vector<double>::iterator i = gear_ratios.begin(); i != gear_ratios.end(); i++)
    {
        n++;
        gears.push_back(VehicleEngine::Gear(max_engine_spins_per_minute * (2 * M_PI / 60) / ((*i) * final_ratio),
                                            max_engine_torque * (*i) * final_ratio, n, (*i) * final_ratio));
    }
    RealEngine r_engine(Position(Vector2D(), 0), VehicleEngine(gears));
    Vector2D mass_center(0, 0);
    mass_center.y += back.y * back.weigth_percent;
    mass_center.y += front.y * front.weigth_percent;
    double raw_square = (width * length + 2 * (width + length) * height);
    double air_resistance = air_resistance_koef * raw_square;
    RealBody r_body(Position(mass_center, mass),
                    VehicleBody(straight_air_koef * air_resistance, back_air_koef * air_resistance,
                                left_air_koef * air_resistance, right_air_koef * air_resistance,
                                rotation_air_koef * air_resistance, mass_center));
    return createVehicle(r, angle, v, angular_speed,
                         Vector2D(0, 0), 0, Vector2D(0, 0), 0,
                         width, length, mass_center_height,
                         r_body, r_engine, turrets, r_wheels);
}

Vehicle* VehicleFactory::createDodgeChallengerSRT8(Vector2D const & r, double angle,
                                        Vector2D const & v, double angular_speed)
{
    std::vector<RealTurret> turrets;
    std::vector<double> gears;
    gears.push_back(3.59);
    gears.push_back(2.19);
    gears.push_back(1.41);
    gears.push_back(1);
    gears.push_back(0.83);
    return createCar(r, angle, v, angular_speed,
                     5.0, 1.923, 1887, 1.45,
                     0.9, 0.025, 1, 1.5, M_PI / 6,
                     CarTrack(-1.62724, 1.604, revsPerKmToRadius(456), 0.466,
                              true, RotationReaction::NoRotation),
                     CarTrack(1.74552, 1.603, revsPerKmToRadius(456), 0.544,
                              false, RotationReaction::StraightRot),
                     0.356, 637, 6000, gears, 3.06, turrets);
}

Vehicle* VehicleFactory::createFerrari599GTO(Vector2D const & r, double angle,
                                        Vector2D const & v, double angular_speed)
{
    std::vector<RealTurret> turrets;
    std::vector<double> gears;
    gears.push_back(3.15);
    gears.push_back(2.18);
    gears.push_back(1.57);
    gears.push_back(1.19);
    gears.push_back(0.94);
    gears.push_back(0.76);
    return createCar(r, angle, v, angular_speed,
                     4.710, 1.962, 1605, 1.326,
                     0.9, 0.025, 1, 1.5, M_PI / 6,
                     CarTrack(-1.328, 1.610, tireSpecsToRadius(315, 35, 20),
                              0.53, false, RotationReaction::NoRotation),
                     CarTrack(1.470, 1.701, tireSpecsToRadius(280, 35, 20),
                              0.47, true, RotationReaction::StraightRot),
                     0.356, 620, 8400, gears, 4.18, turrets);
}
