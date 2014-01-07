#include "vehicle.h"
#include "console.h"

static const double eps = 2e-4;

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

Vehicle::Vehicle(Rectangle2D * shape, double mass, double inertia_moment)
    : PhysicsObject(shape, mass, inertia_moment)
{
    //Console::print("Creating vehicle...");
    this->recalculateMassCenter();
    this->setFiring(false, 0);
    this->setAccelerationState(AccelerationState::NoAcc);
    this->setRotationPercent(0);
    this->setTorquePercent(0);
    this->width = shape->getWidth();
    this->length = shape->getHeight();
    //Console::print("Vehicle has been created.");
}

std::string Vehicle::getType()
{
    return "Vehicle";
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

double Vehicle::getWidth()
{
    return this->width;
}

double Vehicle::getLength()
{
    return this->length;
}

std::vector<PhysicsObject*> Vehicle::calculateFireAndForces(double dt)
{
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
    //Console::print("Chassis force:");
    //Console::print(chassis.f);
    f.add(chassis.f);
    //Console::print("Chassis force moment:");
    //Console::print(chassis.force_moment);
    force_moment += chassis.force_moment;
    body.setSpeed(vr, angular_speed);
    body.calculateForces();
    body.f.rotate(angle);
    //Console::print("Vehicle body force:");
    //Console::print(body.f);
    f.add(body.f);
    //Console::print("Vehicle body force moment:");
    //Console::print(body.force_moment);
    force_moment += body.force_moment;
    double percent;
    std::vector<PhysicsObject*> result;
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
        std::vector<Bullet*> bullets = (*i).calculateFireAndForces(dt);
        for (std::vector<Bullet*>::iterator j = bullets.begin(); j != bullets.end(); j++)
        {
            (*j)->setSource(this);
            (*j)->setMassCenter((*i).r);
            (*j)->move(this->getCoordinates());
            (*j)->rotate(this->getAngle());
            result.push_back(*j);
        }
        (*i).f.rotate(this->getAngle());
        f.add((*i).f);
        force_moment += (*i).force_moment;
    }    
    //Console::print("Total force:");
    //Console::print(f);
    //Console::print(force_moment);
    return result;
}

std::vector<PhysicsObject*> Vehicle::calculateInnerState(double dt)
{
    this->pseudo_v.mul(0);    
    return calculateFireAndForces(dt);
}
