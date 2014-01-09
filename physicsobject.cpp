#include "physicsobject.h"
#include "console.h"

static const double common_pseudo_v_koef = 0.5;
static const double explosion_pseudo_v_koef = 5;
static const double angular_speed_koef = 0.3;
static const double PI = 3.14159265358979323846;
static const double INFINITE_TIME = 1e100;

const QString PhysicsObject::TURRET = "turret";
const QString PhysicsObject::VEHICLE = "vehicle";
const QString PhysicsObject::BULLET = "bullet";
const QString PhysicsObject::EXPLOSION = "explosion";

PhysicsObject::PhysicsObject(Shape2D * shape, double mass, double inertia_moment)
    : shape(shape), mass(mass), inertia_moment(inertia_moment), v(0, 0), a(0, 0), pseudo_v(0, 0),
      f(0, 0), force_moment(0), angular_speed(0), angular_acceleration(0), valid(true), time_to_live(INFINITE_TIME)
{    
    this->dynamic = true;
}

PhysicsObject::~PhysicsObject()
{
    delete shape;
}

Vector2D PhysicsObject::getSpeedAtPoint(const Point2D &point)
{
    Vector2D result = point.toVector();
    result.sub(this->getMassCenter());
    result.rotate(PI / 2);
    result.mul(this->getAngularSpeed());
    result.add(this->getSpeed());
    return result;
}

void PhysicsObject::addImpulseAtPoint(const Vector2D &impulse, const Point2D &point)
{
    Vector2D dv = impulse;
    dv.div(this->mass);
    this->v.add(dv);
    Vector2D r = point.toVector();
    r.sub(this->getMassCenter());
    double d_ang_speed = angular_speed_koef * r.cross(impulse) / this->inertia_moment;
    this->angular_speed += d_ang_speed;
}

void PhysicsObject::pushAwayFromPoint(const Point2D &point, double pseudo_velocity_koef)
{
    Vector2D d_p_v = this->getMassCenter();
    d_p_v.sub(point.toVector());
    d_p_v.setLength(this->shape->getDepth(point) * pseudo_velocity_koef);
    pseudo_v.add(d_p_v);
}

QString PhysicsObject::getType()
{
    return this->physics_object_type;
}

std::vector<PhysicsObject*> PhysicsObject::calculateInnerState(double dt)
{
    return std::vector<PhysicsObject*>();
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
        Vector2D dr = v;
        dr.add(pseudo_v);
        dr.mul(dt);
        move(dr);
        Vector2D dv = a;
        dv.mul(dt);
        v.add(dv);
        a = f;
        a.div(mass);
        rotate(angular_speed * dt);
        angular_speed += angular_acceleration * dt;
        angular_acceleration = (force_moment / inertia_moment) * dt;
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

bool PhysicsObject::collidesWith(PhysicsObject *other)
{
    if ((other->getType() == PhysicsObject::BULLET) || (other->getType() == PhysicsObject::EXPLOSION))
    {
        return other->collidesWith(this);
    }
    else
    {
        return (this->shape->cross(other->shape).crossing);
    }
}

Collision PhysicsObject::solveCollisionWith(PhysicsObject *other)
{
    CrossingResult2D crossing_result = this->shape->cross(other->shape);
    Vector2D collision_center = crossing_result.center.toVector();
    Vector2D relative_speed = this->getSpeedAtPoint(collision_center);
    relative_speed.sub(other->getSpeedAtPoint(collision_center));
    Vector2D collision_direction = relative_speed;
    collision_direction.setLength(1);
    Line2D collision_line(collision_center, collision_direction);
    Vector2D common_direction = this->shape->getGeometryCenter().getVectorTo(other->shape->getGeometryCenter());
    double speed_projection = relative_speed.scalar(common_direction);
    Vector2D impulse_change(0, 0);
    if (speed_projection > 0)
    {
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
    return Collision(collision_center, relative_speed, impulse_change, other);
}

void PhysicsObject::applyCollisions(const std::vector<Collision> &collisions)
{
    pseudo_v.mul(0);
    for (auto i = collisions.begin(); i != collisions.end(); i++)
    {
        QString source_type = i->source->getType();
        if (source_type != PhysicsObject::EXPLOSION)
        {
            addImpulseAtPoint(i->impulse_change, i->collision_center);
        }
        if (source_type != PhysicsObject::BULLET)
        {
            if (source_type == PhysicsObject::EXPLOSION)
            {
                pushAwayFromPoint(i->collision_center, explosion_pseudo_v_koef);
            }
            else
            {
                pushAwayFromPoint(i->collision_center, common_pseudo_v_koef);
            }
        }
    }
}
