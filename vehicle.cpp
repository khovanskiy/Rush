#include "vehicle.h"

static const double G = 9.80665;

Vehicle::Vehicle(Vector2D const & r, double angle,
                 Vector2D const & v, double angular_speed,
                 Vector2D const & f, double force_moment,
                 Vector2D const & a, double angular_acceleration,
                 double mass, double width, double length,
                 Vector2D const & mass_center, double inertia_moment,
                 VehicleBody const & body, Chassis const & chassis,
                 std::vector<Turret> const &turrets)
    : Box(r, angle, v, angular_speed, f, force_moment, a, angular_acceleration,
          mass, width, length), body(body), chassis(chassis), turrets(turrets)
{
    this->mass_center = mass_center;
    this->inertia_moment = inertia_moment;
    this->setFiring(false);
    this->setAccelerationState(NoAcc);
    this->setRotationPercent(0);
    this->setTorquePercent(0);
}

Vehicle::~Vehicle()
{
    chassis.deleteWheels();
}

void Vehicle::setAccelerationState(AccelerationState acc_state)
{
    this->acc_state = acc_state;
}

void Vehicle::setRotationPercent(double rotation_percent)
{
    this->rotation_percent = rotation_percent;
}

void Vehicle::setTorquePercent(double torque_percent)
{
    this->torque_percent = torque_percent;
}

void Vehicle::setFiring(bool firing_state, double firing_angle)
{
    this->firing_angle = firing_angle;
    this->firing_state = firing_state;
}

void Vehicle::calculateFireAndForces(double dt)
{
    f.x = 0;
    f.y = 0;
    force_moment = 0;
    Vector2D vr(v);
    vr.rotate(-angle);
    Vector2D ar(a);
    ar.rotate(-angle);
    chassis.setTotalState(vr, ar, angular_speed, torque_percent,
                          acc_state, rotation_percent);
    chassis.calculateForces(dt);
    chassis.f.rotate(angle);
    f.add(chassis.f);
    force_moment += chassis.force_moment;
    body.setSpeed(vr, angular_speed);
    body.calculateForces(dt);
    body.f.rotate(angle);
    f.add(body.f);
    force_moment += body.force_moment;
    double percent;
    for (std::vector<Turret>::iterator i = turrets.begin(); i != turrets.end(); i++)
    {
        if ((*i).max_angle > 0)
        {
            percent = firing_angle / (*i).max_angle;
            if (percent > 1) percent = 1;
            else if (percent < -1) percent = -1;
            (*i).setAngle(percent);
        }
        else
        {
            (*i).setAngle(0);
        }
        (*i).setFiring(firing_state);
        (*i).calculateFireAndForces(dt);
        f.add((*i).f);
        force_moment += (*i).force_moment;
    }
}

void Vehicle::tick(double dt)
{
    calculateFireAndForces(dt);
    Shape::tick(dt);
}

int Vehicle::getGear()
{
    return chassis.getGear();
}

double Vehicle::getSpins()
{
    return chassis.getSpins();
}
