#ifndef PHYSICSTURRET_H
#define PHYSICSTURRET_H

#include "bullet.h"
#include <QString>
#include <vector>

class Turret : public PhysicsObject
{

    double max_angle;
    int bullet_type;
    double fire_delay, next_shot;

    double scatter;
    bool firing;

    double d_angle;

public:
    static const int MACHINEGUN;
    static const int ROCKET_LAUNCHER;
    static const int SAW;

    Turret(int id, Shape2D * shape, double mass, double fire_delay, double max_angle, int bullet_type, double scatter);
    virtual ~Turret();
    double getMaxAngle() const;
    int turret_type;
    int getTurretType() const;
    void setFiring(bool firing);
    bool getFiring() const;
    GameObjectType getFamilyId();
    virtual void calculateInnerState(double dt);
};

#endif // PHYSICSTURRET_H
