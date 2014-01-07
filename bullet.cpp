#include "bullet.h"
#include "math.h"

static const double infinity = 1e100;

Bullet::Bullet(Vector2D r, Vector2D speed, double mass, BulletType bullet_type, double dt)
    : PhysicsObject(new Segment2D(Point2D(r), Point2D(r).getPoint(speed.getMul(dt))), mass, infinity),
      bullet_type(bullet_type)
{
    switch (bullet_type) {
    case BulletType::Simple:
        this->width = 0.15;
        this->height = 0.43;
        this->time_to_live = 10;
        break;
    default:
        this->width = 0.15;
        this->height = 0.43;
        this->time_to_live = 10;
        break;
    }
    this->v = speed;
    this->setMassCenter(r);
    this->type = "Bullet";
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
    if ((this->source != other) && (other->getType() != "Bullet"))
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



