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
    : PhysicsObject(new Segment2D(Point2D(r), Point2D(r).getPoint(speed.getMul(dt))),
                    mass, infinity, PhysicsObject::BULLET),
      width(width), height(height)
{
    this->v = speed;
    this->setMassCenter(r);
    this->time_to_live = time_to_live;
    this->bullet_type = bullet_type;
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

CrossingResult2D Bullet::collidesWith(PhysicsObject *other)
{
    if ((other->getType() == PhysicsObject::BULLET)
            || (other->getType() == PhysicsObject::EXPLOSION) || (this->source == other))
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }
    else
    {
        return (this->shape->cross(other->getShape()));
    }
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

void Bullet::applyCollision(Collision const &collision, double dt)
{
    Vector2D q = this->getCoordinates();
    q.add(this->getSpeed());
    Segment2D * segment = new Segment2D(Point2D(this->getCoordinates()), Point2D(q));
    setCoordinates(collision.source->getShape()->segmentCrossBorder(segment).toVector());
    delete segment;
    invalidate();
}
