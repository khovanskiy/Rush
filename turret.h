#ifndef PHYSICSTURRET_H
#define PHYSICSTURRET_H
#include "bullet.h"
#include <QString>
#include <vector>

class Turret : public PhysicsObject
{
    friend class PhysicsObjectFactory;
    friend class Vehicle;

    int turret_type;
    double max_angle;
    int bullet_type;
    double fire_delay, next_shot;

    double scatter;
    Vector2D local_r;
    double local_angle;
    bool firing;

    double d_angle;

    Turret(Shape2D * shape, double mass, double inertia_moment,
           double fire_delay, double max_angle, int bullet_type, double scatter);
    virtual ~Turret();


public:
    static const int MACHINEGUN;
    static const int ROCKET_LAUNCHER;
    static const int SAW;

    void setPosition(Vector2D local_r);
    Vector2D getPosition() const;
    int getTurretType() const;
    void setFiring(bool firing);
    bool getFiring() const;
    void setLocalAngle(double local_angle);
    double getLocalAngle() const;
    virtual double getAngle();
    virtual Vector2D getCoordinates();
    virtual std::vector<PhysicsObject*>* calculateInnerState(double dt);
};

#endif // PHYSICSTURRET_H
