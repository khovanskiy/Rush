#include "physicsobject.h"
#include "console.h"

static const double pseudo_velocity_koef = 10;
static const double angular_speed_koef = 0.3;
static const double PI = 3.14159265358979323846;
static const double INFINITE_TIME = 1e100;

int PhysicsObject::next_id = 0;

const int PhysicsObject::TURRET = 0;
const int PhysicsObject::VEHICLE = 1;
const int PhysicsObject::BULLET = 2;
const int PhysicsObject::EXPLOSION = 3;
const int PhysicsObject::OBSTACLE = 4;

PhysicsObject::PhysicsObject(Shape2D * shape, double mass, double inertia_moment, int physics_object_type)
    : shape(shape), mass(mass), inertia_moment(inertia_moment),
      v(0, 0), a(0, 0), pseudo_v(0, 0),
      f(0, 0), force_moment(0), pseudo_angular_speed(0),
      angular_speed(0), angular_acceleration(0),
      valid(true), time_to_live(INFINITE_TIME)
{    
    this->dynamic = true;
    this->physics_object_type = physics_object_type;
    this->id = next_id;
    next_id++;
}

PhysicsObject::~PhysicsObject()
{
    delete shape;
}

Vector2D PhysicsObject::getSpeedAtPoint(const Point2D &point)
{
    Vector2D result = point.toVector();
    result.sub(getMassCenter());
    result.rotate(PI / 2);
    result.mul(angular_speed);
    result.add(v);
    return result;
}

Vector2D PhysicsObject::getPseudoSpeedAtPoint(const Point2D &point)
{
    Vector2D result = point.toVector();
    result.sub(getMassCenter());
    result.rotate(PI / 2);
    result.mul(pseudo_angular_speed);
    result.add(pseudo_v);
    return result;
}

void PhysicsObject::addImpulseAtPoint(const Vector2D &impulse, const Point2D &point)
{
    Vector2D dv = impulse;
    dv.div(mass);
    v.add(dv);
    Vector2D r = point.toVector();
    r.sub(getMassCenter());
    double d_ang_speed = angular_speed_koef * r.cross(impulse) / inertia_moment;
    angular_speed += d_ang_speed;
}

void PhysicsObject::addPseudoImpulseAtPoint(const Vector2D &pseudo_impulse, const Point2D &point)
{
    Vector2D dv = pseudo_impulse;
    dv.div(mass);
    pseudo_v.add(dv);
    Vector2D r = point.toVector();
    r.sub(getMassCenter());
    double d_ang_speed = angular_speed_koef * r.cross(pseudo_impulse) / inertia_moment;
    pseudo_angular_speed += d_ang_speed;
}

int PhysicsObject::getType()
{
    return this->physics_object_type;
}

int PhysicsObject::getId()
{
    return this->id;
}

std::vector<PhysicsObject*>* PhysicsObject::calculateInnerState(double dt)
{
    pseudo_v.mul(0);
    pseudo_angular_speed = 0;
    return 0;
}

bool PhysicsObject::isValid()
{
    return this->valid;
}

void PhysicsObject::invalidate()
{
    this->valid = false;
}

bool PhysicsObject::isDynamic()
{
    return this->dynamic;
}

void PhysicsObject::setStatic()
{
    this->dynamic = false;
}

void PhysicsObject::setDynamic()
{
    this->dynamic = true;
}

void PhysicsObject::tick(double dt)
{
    if ((this->dynamic) && (this->isValid()))
    {
        a = f;
        a.div(mass);
        Vector2D dv = a;
        dv.mul(dt);
        v.add(dv);
        Vector2D dr = v;
        dr.add(pseudo_v);
        dr.mul(dt);
        move(dr);
        angular_acceleration = (force_moment / inertia_moment) * dt;
        angular_speed += angular_acceleration * dt;
        rotate((angular_speed + pseudo_angular_speed) * dt);
    }
    else
    {
        v.mul(0);
        a.mul(0);
        f.mul(0);
        angular_speed = 0;
        angular_acceleration = 0;
        force_moment = 0;
    }
    time_to_live -= dt;
    if (time_to_live <= 0) invalidate();
}

Vector2D PhysicsObject::getCoordinates()
{
    return shape->getGeometryCenter().toVector();
}

void PhysicsObject::setCoordinates(const Vector2D &r)
{
    Vector2D rr = r;
    rr.sub(shape->getGeometryCenter().toVector());
    move(rr);
}

void PhysicsObject::move(const Vector2D &dr)
{
    shape->move(dr.x, dr.y);
}

Vector2D PhysicsObject::getSpeed()
{
    return v;
}

void PhysicsObject::setSpeed(const Vector2D &v)
{
    this->v = v;
}

Vector2D PhysicsObject::getImpulse()
{
    return this->v.getMul(this->mass);
}

double PhysicsObject::getAngle()
{
    return shape->getAngle();
}

void PhysicsObject::setAngle(double angle)
{
    shape->rotate(angle - shape->getAngle());
}

void PhysicsObject::rotate(double angle)
{
    shape->rotate(angle);
}

double PhysicsObject::getAngularSpeed()
{
    return angular_speed;
}

void PhysicsObject::setAngularSpeed(double angular_speed)
{
    this->angular_speed = angular_speed;
}

Vector2D PhysicsObject::getMassCenter()
{
    return shape->getRotatingPoint().toVector();
}

void PhysicsObject::setMassCenter(Vector2D mass_center)
{
    shape->setRotatingPoint(Point2D(mass_center));
}

Shape2D * PhysicsObject::getShape()
{
    return shape;
}

void PhysicsObject::setShape(Shape2D * shape)
{
    delete this->shape;
    this->shape = shape;
}

AABB PhysicsObject::getAABB()
{
    return this->shape->getAABB();
}

double PhysicsObject::getHeight()
{
    return shape->getHeight();
}

double PhysicsObject::getWidth()
{
    return shape->getWidth();
}

double PhysicsObject::getImageHeight()
{
    return shape->getHeight();
}

double PhysicsObject::getImageWidth()
{
    return shape->getWidth();
}

Vector2D PhysicsObject::getRelativeSpeed(PhysicsObject *other)
{
    Vector2D result = this->v;
    result.sub(other->v);
    return result;
}

CrossingResult2D PhysicsObject::collidesWith(PhysicsObject *other)
{
    return this->shape->cross(other->shape);
}

Collision PhysicsObject::solveCollisionWith(PhysicsObject *other, Point2D const & center)
{
    Vector2D collision_center = center.toVector();
    Vector2D relative_speed = this->getSpeedAtPoint(center);
    relative_speed.sub(other->getSpeedAtPoint(center));
    Vector2D common_direction = this->shape->getGeometryCenter().getVectorTo(other->shape->getGeometryCenter());
    Vector2D impulse_change(0, 0);
    if (relative_speed.scalar(common_direction) > 0)
    {
        Vector2D collision_direction = relative_speed;
        collision_direction.setLength(1);
        Vector2D r1 = collision_center;
        r1.sub(this->getMassCenter());
        double k1 = r1.cross(collision_direction);
        k1 = angular_speed_koef * k1 * k1 / this->inertia_moment;
        Vector2D r2 = collision_center;
        r2.sub(other->getMassCenter());
        double k2 = r2.cross(collision_direction);
        k2 = angular_speed_koef * k2 * k2 / other->inertia_moment;
        double impulse = relative_speed.getLength() / (1 / this->mass + 1 / other->mass + k1 + k2);
        impulse_change = collision_direction;
        impulse_change.mul(-impulse);
    }
    Vector2D relative_pseudo_speed = this->getPseudoSpeedAtPoint(center);
    relative_pseudo_speed.sub(other->getPseudoSpeedAtPoint(center));
    double depth = shape->getDepth(center) + other->getShape()->getDepth(center);
    Vector2D push_speed = common_direction;
    push_speed.setLength(pseudo_velocity_koef * depth);
    relative_pseudo_speed.add(push_speed);
    Vector2D pseudo_impulse_change(0, 0);
    if (relative_pseudo_speed.scalar(common_direction) > 0)
    {
        Vector2D collision_direction = relative_pseudo_speed;
        collision_direction.setLength(1);
        Vector2D r1 = collision_center;
        r1.sub(this->getMassCenter());
        double k1 = r1.cross(collision_direction);
        k1 = angular_speed_koef * k1 * k1 / this->inertia_moment;
        Vector2D r2 = collision_center;
        r2.sub(other->getMassCenter());
        double k2 = r2.cross(collision_direction);
        k2 = angular_speed_koef * k2 * k2 / other->inertia_moment;
        double pseudo_impulse = relative_pseudo_speed.getLength() / (1 / this->mass + 1 / other->mass + k1 + k2);
        pseudo_impulse_change = common_direction;
        pseudo_impulse_change.setLength(-pseudo_impulse);
    }
    return Collision(collision_center, impulse_change, pseudo_impulse_change, depth, other);
}

void PhysicsObject::applyCollision(const Collision &collision, double dt)
{
    addImpulseAtPoint(collision.impulse_change, collision.center);
    addPseudoImpulseAtPoint(collision.pseudo_impulse_change, collision.center);
}

double PhysicsObject::getMass()
{
    return this->mass;
}

double PhysicsObject::getInertiaMoment()
{
    return this->inertia_moment;
}

bool PhysicsObject::isProjectile()
{
    return false;
}
