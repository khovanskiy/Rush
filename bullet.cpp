#include "bullet.h"

static const double infinity = 1e100;

Bullet::Bullet(Vector2D r, Vector2D speed, double mass, int bullet_id)
    : PhysicsObject(new Segment2D(Point2D(r), Point2D(r).getPoint(speed)), mass, infinity),
      bullet_id(bullet_id)
{
}

void Bullet::setSource(PhysicsObject *source)
{
    this->source = source;
}

std::string Bullet::getType()
{
    return "Bullet";
}
