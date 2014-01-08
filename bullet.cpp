#include "bullet.h"
#include "math.h"

static const double infinity = 1e100;

const QString Bullet::BULLET = "bullet";
const QString Bullet::MISSILE = "missile";
const QString Bullet::CUT = "cut";

Bullet::Bullet(Vector2D r, Vector2D speed, double mass, QString bullet_type,
               double width, double height, double dt, double time_to_live)
    : PhysicsObject(new Segment2D(Point2D(r), Point2D(r).getPoint(speed.getMul(dt))), mass, infinity),
      bullet_type(bullet_type), width(width), height(height)
{
    this->v = speed;
    this->setMassCenter(r);
    this->physics_object_type = PhysicsObject::BULLET;
    this->time_to_live = time_to_live;
}

void Bullet::setSource(PhysicsObject *source)
{
    this->source = source;
}

Bullet::~Bullet()
{
}

bool Bullet::collidesWith(PhysicsObject *other, double dt)
{
    if ((this->source != other) && (other->getType() != PhysicsObject::BULLET))
    {
        bool result = (this->PhysicsObject::collidesWith(other, dt));
        if (result) invalidate();
        return result;
    }
    else
    {
        return false;
    }
}

Collision Bullet::solveCollisionWith(PhysicsObject *other, double dt)
{
    return this->PhysicsObject::solveCollisionWith(other, dt);
}

double Bullet::getWidth()
{
    return this->width;
}

double Bullet::getHeight()
{
    return this->height;
}

QString Bullet::getBulletType()
{
    return this->bullet_type;
}


