#ifndef PHYSICSVEHICLEBODY_H
#define PHYSICSVEHICLEBODY_H
#include "vector2d.h"

struct VehicleBody
{
    double front_air_resistance;
    double rear_air_resistance;
    double left_air_resistance;
    double right_air_resistance;
    double spin_air_resistance;
    Vector2D r;

    Vector2D v;
    Vector2D f;
    double angular_speed;
    double environment_resistance;
    double force_moment;


    VehicleBody(
            double front_air_resistance,
            double rear_air_resistance,
            double left_air_resistance,
            double right_air_resistance,
            double spin_air_resistance,
            Vector2D const & r);
    VehicleBody(VehicleBody const & body);
    void setEnvironmentResistance(double environment_resistance);
    void setSpeed(Vector2D const & v, double angular_speed);
    double getChangedResistance(double resistance);
    void calculateForces();
};

#endif // PHYSICSVEHICLEBODY_H
