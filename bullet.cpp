#include "bullet.h"
#include "math.h"
#include "explosion.h"
#include "physicsobjectfactory.h"

static const double infinity = 1e100;

const int Bullet::BULLET = 0;
const int Bullet::MISSILE = 1;
const int Bullet::CUT = 2;

Bullet::Bullet(Vector2D r, Vector2D speed, double mass, int bullet_type,
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

GameObjectType Bullet::getFamilyId()
{
    return GameObjectType::BULLET;
}

void Bullet::setSource(PhysicsObject *source)
{
    this->source = source;
}

Bullet::~Bullet()
{
    Console::print("Bullet is deleted");
}

CrossingResult2D Bullet::collidesWith(PhysicsObject *other)
{
    if (this->source == other)
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }
    else
    {
        return (this->shape->cross(other->getShape()));
    }
}

int Bullet::getBulletType()
{
    return this->bullet_type;
}

void Bullet::applyCollision(Collision const &collision, double dt)
{
    Console::print("DAMAGE");
    Vector2D q = this->getCoordinates();
    q.add(this->getSpeed());
    Segment2D * segment = new Segment2D(Point2D(this->getCoordinates()), Point2D(q));
    setCoordinates(collision.source->getShape()->segmentCrossBorder(segment).toVector());
    delete segment;
    invalidate();
}

void Bullet::calculateInnerState(double dt)
{
    PhysicsObject::calculateInnerState(dt);
    //Console::print(getCoordinates());
    if (!isValid() && bullet_type == Bullet::MISSILE)
    {
        std::vector<PhysicsObject*>* result = new std::vector<PhysicsObject*>();
        /*result->push_back(PhysicsObjectFactory::createExplosion(
                             this->getCoordinates(),
                             this->getAngle(),
                             Explosion::MEDIUM));*/
        return;// result;
    }
    else
    {
        return;// 0;
    }
}

bool Bullet::isProjectile()
{
    return true;
}
