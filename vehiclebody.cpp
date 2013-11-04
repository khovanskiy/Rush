#include "vehiclebody.h"
#include <math.h>

VehicleBody::VehicleBody(double front_air_resistance,
                                       double rear_air_resistance,
                                       double left_air_resistance,
                                       double right_air_resistance,
                                       double spin_air_resistance,
                                       Vector2D const & r)
    : r(r)
{
    this->front_air_resistance = front_air_resistance;
    this->rear_air_resistance = rear_air_resistance;
    this->left_air_resistance = left_air_resistance;
    this->right_air_resistance = right_air_resistance;
    this->spin_air_resistance = spin_air_resistance;
    this->environment_resistance = 1;
}

VehicleBody::VehicleBody(VehicleBody const & body)
{
    this->front_air_resistance = body.front_air_resistance;
    this->rear_air_resistance = body.rear_air_resistance;
    this->left_air_resistance = body.left_air_resistance;
    this->right_air_resistance = body.right_air_resistance;
    this->spin_air_resistance = body.spin_air_resistance;
    this->r = body.r;
    this->environment_resistance = body.environment_resistance;
}

void VehicleBody::setSpeed(Vector2D const & v, double angular_speed)
{
    this->v = v;
    this->angular_speed = angular_speed;
}

void VehicleBody::setEnvironmentResistance(double environment_resistance)
{
    this->environment_resistance = environment_resistance;
}

double VehicleBody::getChangedResistance(double resistance)
{
    return resistance * environment_resistance;
}

void VehicleBody::calculateForces(double dt)
{
    double vl = v.getLength();
    if (vl > 0)
    {
        double vertical_resistance =
                (v.y > 0 ? getChangedResistance(front_air_resistance) : getChangedResistance(rear_air_resistance));
        double horizontal_resistance =
                (v.x > 0 ? getChangedResistance(right_air_resistance) : getChangedResistance(left_air_resistance));
        f.x = - v.x * vl * horizontal_resistance;
        if (abs(f.x) > abs(v.x / dt))
        {
            f.x = -v.x / dt;
        }
        f.y = - v.y * vl * vertical_resistance;
        if (abs(f.y) > abs(v.y / dt))
        {
            f.y = -v.y / dt;
        }
        force_moment = r.cross(f);
    }
    else
    {
        f.x = 0;
        f.y = 0;
        force_moment = 0;
    }
    force_moment -= angular_speed * abs(angular_speed) * getChangedResistance(spin_air_resistance);
}




