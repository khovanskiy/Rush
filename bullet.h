<<<<<<< HEAD
#ifndef PHYSICSBULLET_H
#define PHYSICSBULLET_H
#include "materialpoint.h"

struct Bullet //: public MaterialPoint
{
    double damage;
    double speed;
    double angle;
    PhysicsObject * owner;

    Bullet();
    //Bullet(Vector2D const & r, double speed, double angle,
           //double mass, double damage, PhysicsObject* owner);
=======
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

    Bullet(Vector2D r, Vector2D speed, double mass, QString bullet_type,
           double width, double height, double dt, double time_to_live);
    virtual ~Bullet();

public:
    static const QString BULLET;
    static const QString MISSILE;
    static const QString CUT;

    void setSource(PhysicsObject* source);
    virtual CrossingResult2D collidesWith(PhysicsObject *other);
    virtual double getWidth();
    virtual double getHeight();
    virtual QString getBulletType();
    virtual void invalidate();
    virtual void applyCollision(const Collision &collision, double dt);
>>>>>>> origin/physicsDebug
};

#endif // BULLET_H
