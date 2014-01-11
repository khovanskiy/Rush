#include "vehicle.h"
#include "console.h"

static const double eps = 2e-4;

const QString Vehicle::DODGE_CHALLENGER_SRT8 = "dodge_challenger_srt8";
const QString Vehicle::FERRARI_599GTO = "ferrari_599_gto";

void Vehicle::recalculateMassCenter()
{
    this->mass_center = this->shape->getRotatingPoint().toVector();
    this->mass_center.sub(this->shape->getGeometryCenter().toVector());
    this->mass_center.rotate(-this->shape->getAngle());
    chassis.setStructure(this->mass, this->mass_center, this->height);
    body.r = this->mass_center;
}

void Vehicle::setMassCenter(Vector2D mass_center)
{
    this->PhysicsObject::setMassCenter(mass_center);
    this->recalculateMassCenter();
}

Vehicle::Vehicle(Rectangle2D * shape, double mass, double inertia_moment, QString vehicle_type)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::VEHICLE)
{
    this->recalculateMassCenter();
    this->setFiring(false, 0);
    this->setAccelerationState(AccelerationState::NoAcc);
    this->setRotationPercent(0);
    this->setTorquePercent(0);
    this->width = shape->getWidth();
    this->length = shape->getHeight();
    this->vehicle_type = vehicle_type;
}

Vehicle::~Vehicle()
{
    for (auto i = turrets.begin(); i != turrets.end(); i++)
    {
        delete *i;
    }
}

void Vehicle::setVehicleBody(const VehicleBody &body)
{
    this->body = body;
    this->recalculateMassCenter();
}

void Vehicle::setWheels(CarTrack back, CarTrack front, double height)
{
    this->height = height;
    this->chassis.setWheels(this->mass, this->height, back, front);
    Vector2D m_c = chassis.getMassCenter();
    m_c.rotate(this->getAngle());
    m_c.add(this->getCoordinates());
    setMassCenter(m_c);
}

void Vehicle::setEngine(const VehicleEngine &engine)
{
    this->chassis.setEngine(engine);
}

void Vehicle::addTurret(Turret * turret)
{
    this->turrets.push_back(turret);
}

void Vehicle::setAccelerationState(AccelerationState const & acc_state)
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

int Vehicle::getGear()
{
    return chassis.getGear();
}

double Vehicle::getSpins()
{
    return chassis.getSpins();
}

bool Vehicle::isStaying()
{
    return ((v.getLength() < eps) && (angular_speed < eps));
}

std::vector<PhysicsObject*> Vehicle::calculateInnerState(double dt)
{
    PhysicsObject::calculateInnerState(dt);
    double angle = this->shape->getAngle();
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
    body.calculateForces();
    body.f.rotate(angle);
    f.add(body.f);
    force_moment += body.force_moment;
    std::vector<PhysicsObject*> result;
    for (std::vector<Turret*>::iterator i = turrets.begin(); i != turrets.end(); i++)
    {
        (*i)->setLocalAngle(firing_angle);
        (*i)->setFiring(firing_state);
        std::vector<PhysicsObject*> bullets = (*i)->calculateInnerState(dt);
        double angle = this->getAngle();
        Vector2D r = (*i)->getPosition();
        r.rotate(angle);
        r.add(this->getMassCenter());
        for (std::vector<PhysicsObject*>::iterator j = bullets.begin(); j != bullets.end(); j++)
        {
            (dynamic_cast<Bullet*>(*j))->setSource(this);
            Vector2D ddr = (*j)->getCoordinates();
            ddr.rotate(angle);
            ddr.add(this->getMassCenter());
            (*j)->setMassCenter((*j)->getCoordinates());
            (*j)->rotate(angle);
            (*j)->setCoordinates(ddr);
            Vector2D v = (*j)->getSpeed();
            v.rotate(angle);
            v.add(this->getSpeed());
            (*j)->setSpeed(v);
            Vector2D impulse = (*j)->getImpulse();
            impulse.mul(-1);
            this->addImpulseAtPoint(impulse, r);
            result.push_back(*j);
        }
    }
    return result;
}

QString Vehicle::getVehicleType()
{
    return this->vehicle_type;
}

std::vector<Turret*> Vehicle::getTurrets()
{
    return this->turrets;
}

void Vehicle::invalidate()
{
    for (auto i = turrets.begin(); i != turrets.end(); i++)
    {
        (*i)->invalidate();
    }
}

void Vehicle::tick(double dt)
{
    this->PhysicsObject::tick(dt);
    for (auto i = turrets.begin(); i != turrets.end(); i++)
    {
        double angle = this->getAngle();
        Vector2D r = (*i)->getPosition();
        r.rotate(angle);
        r.add(this->getMassCenter());
        (*i)->setCoordinates(r);
        (*i)->setAngle((*i)->getLocalAngle() + angle);
    }
}
