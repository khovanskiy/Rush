#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "physicsobject.h"

class Explosion : public PhysicsObject
{
    double time;
    double start_radius;
    double end_radius;

    QString explosion_type;

public:

    static const QString SMALL;
    static const QString MEDIUM;
    static const QString LARGE;

    Explosion(Shape2D* shape, double mass, double inertia_moment,
              double start_radius, double end_radius, double time,
              QString explosion_type);
    QString getExplosionType();
    virtual void tick(double dt);
    virtual bool collidesWith(PhysicsObject *other);
    virtual void applyCollisions(const std::vector<Collision> &collisions);
};

#endif // EXPLOSION_H
