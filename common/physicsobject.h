#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "gamemodelobject.h"

#include "geometry2d.h"
#include "matrix.h"
#include <vector>
#include <QString>

class PhysicsObject;

class Collision
{
public:
    Vector2D center;
    Vector2D normal;
    Vector2D relative_speed;
    Vector2D impulse_change;
    PhysicsObject* source;

    Collision(){}
    Collision(Vector2D center, Vector2D normal, Vector2D relative_speed, Vector2D impulse_change, PhysicsObject* source)
        : center(center), normal(normal), relative_speed(relative_speed), impulse_change(impulse_change)
    {
        this->source = source;
    }
};

class PhysicsObject : public GameModelObject
{
protected:
    Shape2D * shape;
    Vector2D v;
    Vector2D a;
    Vector2D f;
    Vector2D pseudo_v;
    double mass, inertia_moment, force_moment;
    double angular_speed, angular_acceleration;
    int physics_object_type;
    bool dynamic;
    double time_to_live;

    PhysicsObject(int id, Shape2D* shape, double mass, double inertia_moment, int physics_object_type);
    virtual ~PhysicsObject();

    Vector2D getSpeedAtPoint(Point2D const & point);

    void addImpulseAtPoint(Vector2D const & impulse, Point2D const & point);
    void pushAwayFromPoint(Point2D const & point, Vector2D const & normal, PhysicsObject* source, double dt);
    void pushAwayFromExplosion(Point2D const & center, double radius, double impulse_change);

    Matrix* local_matrix;
public:
    static const int TURRET;
    static const int VEHICLE;
    static const int BULLET;
    static const int EXPLOSION;
    static const int OBSTACLE;

    QString debug;

    Matrix& getTransform();

    virtual void tick(double dt);
    virtual void calculateInnerState(double dt);

    virtual int getType();
    virtual bool isDynamic();
    virtual void setStatic();
    virtual void setDynamic();
    virtual bool isProjectile();

    virtual void applyCollision(Collision const & collision, double dt);
    virtual Vector2D getCoordinates() const;
    virtual void setCoordinates(Vector2D const & r);

    virtual void move(Vector2D const & dr);
    virtual Vector2D getSpeed();
    virtual void setSpeed(Vector2D const & v);
    virtual Vector2D getImpulse();
    virtual double getAngle();
    virtual void setAngle(double angle);
    virtual void rotate(double angle);
    virtual double getAngularSpeed();
    virtual void setAngularSpeed(double angular_speed);
    virtual Vector2D getMassCenter();
    virtual void setMassCenter(Vector2D mass_center);
    virtual Shape2D * getShape();
    virtual void setShape(Shape2D* shape);
    virtual AABB getAABB();
    virtual double getHeight();
    virtual double getWidth();
    virtual double getMass() const;
    virtual double getInertiaMoment() const;
    virtual Vector2D getRelativeSpeed(PhysicsObject* other);
    virtual CrossingResult2D collidesWith(PhysicsObject* other);
    virtual Collision solveCollisionWith(PhysicsObject* other, Point2D const & center, Vector2D const & normal);
};

#endif // PHYSICSOBJECT_H
