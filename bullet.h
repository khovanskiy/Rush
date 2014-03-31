#ifndef BULLET_H
#define BULLET_H

#include "physicsobject.h"
#include <QString>

class Bullet : public PhysicsObject
{
    friend class PhysicsObjectFactory;

    int bullet_type;
    PhysicsObject* source;
    double width, height;

public:
    static const int BULLET;
    static const int MISSILE;
    static const int CUT;

    Bullet(Vector2D r, Vector2D speed, double mass, int bullet_type,
           double width, double height, double dt, double time_to_live);
    virtual ~Bullet();

    GameObjectType getFamilyId();

    void setSource(PhysicsObject* source);
    virtual CrossingResult2D collidesWith(PhysicsObject *other);
    virtual int getBulletType();    
    virtual void applyCollision(const Collision &collision, double dt);
    virtual void calculateInnerState(double dt);
    virtual bool isProjectile();
};

#endif // BULLET_H
