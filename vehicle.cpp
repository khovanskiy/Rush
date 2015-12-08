#include "vehicle.h"
#include "console.h"

#include <cmath>
#include "gameobjectevent.h"

static const double eps = 2e-4;
//static const double M_PI = 3.14159265358979323846;

const int Vehicle::DODGE_CHALLENGER_SRT8 = 0;
const int Vehicle::FERRARI_599GTO = 1;
const int Vehicle::FORD_F150_SVT_RAPTOR = 2;

void Vehicle::recalculateMassCenter()
{
    this->mass_center = this->shape->getRotatingPoint().toVector();
    this->mass_center.sub(this->shape->getGeometryCenter().toVector());
    this->mass_center.rotate(-this->shape->getAngle());
    chassis.setStructure(this->mass, this->mass_center, this->height);
    body.r = this->mass_center;
}

void Vehicle::Invoke(const Event &event)
{
    if (event.type == "TURRET_FIRE")
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        GameObjectEvent e2(this, "TURRET_FIRE", e->position);
        e2.type_object = e->type_object;
        dispatchEvent(e2);
    }
}

GameObjectType Vehicle::getFamilyId()
{
    return GameObjectType::VEHICLE;
}

void Vehicle::setMassCenter(Vector2D mass_center)
{
    this->PhysicsObject::setMassCenter(mass_center);
    this->recalculateMassCenter();
}

Vehicle::Vehicle(int id, Rectangle2D * shape, int mass) : PhysicsObject(id, shape, mass, shape->getInertiaMoment(mass), PhysicsObject::VEHICLE)
{
    this->recalculateMassCenter();
    this->setFiring(false);
    this->setAccelerationState(AccelerationState::NoAcc);
    this->setRotationPercent(0);
    this->setTorquePercent(0);
    this->width = shape->getWidth();
    this->length = shape->getHeight();
    health = 100;
}

Vehicle::~Vehicle()
{
    for (int i = 0; i < turrets.size(); ++i)
    {
        delete turrets[i];
    }
    Console::print("Vehicle is deleted");
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

void Vehicle::addTurret(Turret* turret)
{
    turret->addEventListener(this);

    this->turrets.push_back(turret);
    this->mass += turret->getMass();
    this->inertia_moment += turret->getInertiaMoment();
    double d = turret->getCoordinates().getLength();
    this->inertia_moment += d * d * turret->getMass();

    dispatchEvent(GameObjectEvent(this, GameObjectEvent::ADDED_OBJECT, turret));
}

void Vehicle::invalidate()
{
    //Console::print("Vehicle is invalidated");
    for (int i = 0; i < turrets.size(); ++i)
    {
        turrets[i]->invalidate();
    }
    GameModelObject::invalidate();
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

void Vehicle::setFiring(bool firing_state)
{
    this->firing_state = firing_state;
}

void Vehicle::turretsToPoint(const Vector2D &target)
{
    for (std::vector<Turret*>::iterator i = turrets.begin(); i != turrets.end(); ++i)
    {
        Turret* t = *i;
        Matrix m = Matrix::mul(getTransform(), t->getTransform());

        Vector2D v = m.map(target);
        t->rotate(-atan2(v.x, v.y));
    }
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

void Vehicle::applyCollision(const Collision &collision, double dt)
{
    PhysicsObject::applyCollision(collision, dt);
    if (collision.source->getFamilyId() == GameObjectType::BULLET)
    {
        Bullet* bullet = static_cast<Bullet*>(collision.source);
        health -= bullet->getDamage();
        if (health <= 0)
        {
            PhysicsObject* phy_obj = bullet->getSource();
            if (phy_obj)
            {
                if (phy_obj->getFamilyId() == GameObjectType::VEHICLE)
                {
                    dispatchEvent(GameObjectEvent(this, "DESTROY_BY", phy_obj));
                }
            }
        }
    }
    else if (collision.source->getFamilyId() == GameObjectType::OBSTACLE)
    {
        health -= std::max(0.0, collision.relative_speed.getLength() - 10.0);
    }
    else if (collision.source->getFamilyId() == GameObjectType::VEHICLE)
    {
        Vehicle* other = static_cast<Vehicle*>(collision.source);
        double k  = other->getSpeed().getLength() / this->getSpeed().getLength();
        health -= std::max(0.0, (collision.relative_speed.getLength() - 10.0) * k);
    }
    if (health <= 0)
    {
        invalidate();
    }
}

void Vehicle::calculateInnerState(double dt)
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

    for (std::vector<Turret*>::iterator i = turrets.begin(); i != turrets.end(); i++)
    {
        (*i)->setFiring(firing_state);
        (*i)->calculateInnerState(dt);

        //(*i)->setAngle(firing_angle);
        //(*i)->setFiring(firing_state);
        /*std::vector<PhysicsObject*>* bullets = (*i)->calculateInnerState(dt);
        double angle = this->getAngle();
        Vector2D r = (*i)->getCoordinates();
        r.rotate(angle);
        r.add(this->getMassCenter());
        if (bullets != 0)
        {
            for (std::vector<PhysicsObject*>::iterator j = bullets->begin(); j != bullets->end(); j++)
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
                (*j)->setAngle(-asin(1) + atan2(v.y, v.x));
                Vector2D impulse = (*j)->getImpulse();
                impulse.mul(-1);
                this->addImpulseAtPoint(impulse, r);
                result->push_back(*j);
            }
            delete bullets;
        }*/
    }
    return;// result;
}

int Vehicle::getVehicleType()
{
    return this->vehicle_type;
}

std::vector<Turret*> Vehicle::getTurrets()
{
    return this->turrets;
}

void Vehicle::tick(double dt)
{
    this->PhysicsObject::tick(dt);
}
