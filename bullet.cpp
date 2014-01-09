#include "bullet.h"
#include "math.h"
#include "physicsworld.h"
#include "explosion.h"
#include "physicsobjectfactory.h"

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

void Bullet::invalidate()
{
    this->PhysicsObject::invalidate();
    if (bullet_type == Bullet::MISSILE)
    {
        if (!PhysicsWorld::gi().isClosed())
        {
            PhysicsObjectFactory::createExplosion(this->getCoordinates(), this->getAngle(), Explosion::MEDIUM);
        }
    }
}

bool Bullet::collidesWith(PhysicsObject *other)
{
    bool result = (this->source != other) && (other->getType() != PhysicsObject::BULLET)
            && (other->getType() != PhysicsObject::EXPLOSION)
            && (this->shape->cross(other->getShape()).crossing);
    if (result)
    {
        Vector2D q = this->getCoordinates();
        q.add(this->getSpeed());
        Segment2D * segment = new Segment2D(Point2D(this->getCoordinates()), Point2D(q));
        setCoordinates(other->getShape()->segmentCrossBorder(segment).toVector());
        delete segment;
        invalidate();
    }
    return result;
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

void Bullet::applyCollisions(const std::vector<Collision> &collisions)
{
}
