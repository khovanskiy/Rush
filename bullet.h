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

    Bullet(Vector2D r, Vector2D speed, double mass, int bullet_type,
           double width, double height, double dt, double time_to_live);
    virtual ~Bullet();

public:
    static const int BULLET;
    static const int MISSILE;
    static const int CUT;

    void setSource(PhysicsObject* source);
    virtual CrossingResult2D collidesWith(PhysicsObject *other);
    virtual double getWidth();
    virtual double getHeight();
    virtual int getBulletType();    
    virtual void applyCollision(const Collision &collision, double dt);
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
};

#endif // BULLET_H
