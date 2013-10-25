#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

class PhysicsObject
{
public:
    double x, y, angle;
    double vx, vy, angular_speed;
    double fx, fy, force_moment;
    double ax, ay, angular_acceleration;
    double mass, inertia_moment;
    PhysicsObject(double x, double y, double angle,
                  double vx, double vy, double angular_speed,
                  double fx, double fy, double force_moment,
                  double ax, double ay, double angular_acceleration,
                  double mass, double inertia_moment);
    virtual void tick(double dt);
};

#endif // PHYSICSOBJECT_H
