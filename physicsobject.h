#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "geometry2d.h"
#include <vector>
#include <string>

class PhysicsObject;

struct Collision
{
    Vector2D collision_center;
    Vector2D relative_speed;
    Vector2D impulse_change;
    PhysicsObject* source;

    Collision(Vector2D collision_center, Vector2D relative_speed,
              Vector2D impulse_change, PhysicsObject* source)
        : collision_center(collision_center), relative_speed(relative_speed),
          impulse_change(impulse_change)
    {
        this->source = source;
    }
};

class PhysicsObject
{
protected:
    Shape2D * shape;
    Vector2D v, a, f, pseudo_v;
    double mass, inertia_moment, force_moment;
    double angular_speed, angular_acceleration;
    std::string type;
    bool valid;
    double time_to_live;

    Vector2D getSpeedAtPoint(Point2D const & point);
    void addImpulseAtPoint(Vector2D const & impulse, Point2D const & point, double dt);
    void pushAwayFromPoint(Point2D const & point);    

public:
    PhysicsObject(Shape2D* shape, double mass, double inertia_moment);
    virtual ~PhysicsObject();
    virtual std::string getType();
    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    virtual bool isValid();
    virtual void invalidate();
    virtual void tick(double dt);
    virtual Vector2D getCoordinates();
    virtual void setCoordinates(Vector2D const & r);
    virtual void move(Vector2D const & dr);
    virtual Vector2D getSpeed();
    virtual void setSpeed(Vector2D const & v);
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
    virtual bool collidesWith(PhysicsObject* other, double dt);
    virtual Collision solveCollisionWith(PhysicsObject* other, double dt);
    virtual void applyCollision(Collision const & collision, double dt);
};

#endif // PHYSICSOBJECT_H
