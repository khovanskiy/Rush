#ifndef BULLET_H
#define BULLET_H
#include "physicsobject.h"

enum BulletType
{
    Simple
};

struct Bullet : public PhysicsObject
{
    BulletType bullet_type;
    PhysicsObject* source;
    double width, height;

    Bullet(Vector2D r, Vector2D speed, double mass, BulletType bullet_type, double dt);
    virtual ~Bullet();
    void setSource(PhysicsObject* source);
    virtual bool collidesWith(PhysicsObject *other, double dt);
    virtual Collision solveCollisionWith(PhysicsObject *other, double dt);
    virtual double getWidth();
    virtual double getHeight();

};

#endif // BULLET_H
