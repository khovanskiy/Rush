#ifndef PHYSICSVEHICLEBODY_H
#define PHYSICSVEHICLEBODY_H
#include "vector2d.h"

struct PhysicsVehicleBody
{
    //Constants for this vehicle body.
    //Vector r is relative to the mass centre of vehicle.

    double front_air_resistance;
    double rear_air_resistance;
    double left_air_resistance;
    double right_air_resistance;
    double spin_air_resistance;
    Vector2D r;

    //Current state of vehicle body;

    Vector2D v;
    Vector2D f;
    double angular_speed;
    double environment_resistance;
    double force_moment;


    PhysicsVehicleBody(
            double front_air_resistance,
            double rear_air_resistance,
            double left_air_resistance,
            double right_air_resistance,
            double spin_air_resistance,
            Vector2D r);
    void setEnvironmentResistance(double environment_resistance);
    void setSpeed(Vector2D v, double angular_speed);
    double getChangedResistance(double resistance);
    void calculateForces(double dt);
};

#endif // PHYSICSVEHICLEBODY_H
