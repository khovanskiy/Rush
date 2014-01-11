#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "physicsobject.h"

class Explosion : public PhysicsObject
{
    friend class PhysicsObjectFactory;

    double time;
    double start_radius;
    double end_radius;
    double explosion_impulse;

    QString explosion_type;

    Explosion(Shape2D* shape, double mass, double inertia_moment,
              double start_radius, double end_radius, double time,
              double explosion_impulse, QString explosion_type);

public:

    static const QString SMALL;
    static const QString MEDIUM;
    static const QString LARGE;

    QString getExplosionType();
    virtual void tick(double dt);
    virtual CrossingResult2D collidesWith(PhysicsObject *other);
    virtual Collision solveCollisionWith(PhysicsObject *other, const Point2D &center);
    virtual void applyCollision(const Collision &collision, double dt);
};

#endif // EXPLOSION_H
