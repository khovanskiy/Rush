#ifndef BULLET_H
#define BULLET_H
#include "physicsobject.h"
#include <QString>

class Bullet : public PhysicsObject
{
    friend class PhysicsObjectFactory;

    QString bullet_type;
    PhysicsObject* source;
    double width, height;

public:
    static const QString BULLET;
    static const QString MISSILE;
    static const QString CUT;

    Bullet(Vector2D r, Vector2D speed, double mass, QString bullet_type,
           double width, double height, double dt, double time_to_live);
    virtual ~Bullet();

    void setSource(PhysicsObject* source);
    virtual bool collidesWith(PhysicsObject *other, double dt);
    virtual Collision solveCollisionWith(PhysicsObject *other, double dt);
    virtual double getWidth();
    virtual double getHeight();
    virtual QString getBulletType();

};

#endif // BULLET_H
