#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "geometry2d.h"
#include <vector>
#include <QString>

class PhysicsObject;

struct Collision
{
    Vector2D center;
    Vector2D relative_speed;
    Vector2D impulse_change;
    PhysicsObject* source;

    Collision(){}
    Collision(Vector2D center, Vector2D relative_speed,
              Vector2D impulse_change, PhysicsObject* source)
        : center(center), relative_speed(relative_speed),
          impulse_change(impulse_change)
    {
        this->source = source;
    }
};

class PhysicsObject
{
    friend class PhysicsWorld;
    friend class PhysicsObjectFactory;
    friend struct ObjectData;

    static int next_id;

protected:
    Shape2D * shape;
    Vector2D v, a, f, pseudo_v;
    double mass, inertia_moment, force_moment;
    double angular_speed, angular_acceleration;
    QString physics_object_type;
    bool dynamic;
    bool valid;
    int id;
    double time_to_live;

    PhysicsObject(Shape2D* shape, double mass, double inertia_moment, QString physics_object_type);
    virtual ~PhysicsObject();

    Vector2D getSpeedAtPoint(Point2D const & point);
    void addImpulseAtPoint(Vector2D const & impulse, Point2D const & point);
    void pushAwayFromPoint(Point2D const & point, PhysicsObject* source, double dt);
    void pushAwayFromExplosion(Point2D const & center, double radius);

public:
    static const QString TURRET;
    static const QString VEHICLE;
    static const QString BULLET;
    static const QString EXPLOSION;
    static const QString OBSTACLE;

    virtual QString getType();
    virtual int getId();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    virtual bool isValid();
    virtual void invalidate();
    virtual bool isDynamic();
    virtual void setStatic();
    virtual void setDynamic();
    virtual void tick(double dt);
    virtual Vector2D getCoordinates();
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
    virtual Vector2D getRelativeSpeed(PhysicsObject* other);
    virtual CrossingResult2D collidesWith(PhysicsObject* other);
    virtual Collision solveCollisionWith(PhysicsObject* other, Point2D const & center);
    virtual void applyCollision(Collision const & collision, double dt);
};

#endif // PHYSICSOBJECT_H
