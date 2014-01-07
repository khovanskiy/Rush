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

    double getChangedResistance(double resistance);

    VehicleBody();
    VehicleBody(
            double front_air_resistance,
            double rear_air_resistance,
            double left_air_resistance,
            double right_air_resistance,
            double spin_air_resistance,
            Vector2D const & r);
    VehicleBody(double air_resistance_koef, double length, double width, double height, Vector2D r);
    VehicleBody(VehicleBody const & body);
    void setEnvironmentResistance(double environment_resistance);
    void setSpeed(Vector2D const & v, double angular_speed);
    void calculateForces();
};

#endif // PHYSICSVEHICLEBODY_H
