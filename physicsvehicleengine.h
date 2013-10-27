#ifndef PHYSICSVEHICLEENGINE_H
#define PHYSICSVEHICLEENGINE_H
#include <vector>

struct PhysicsVehicleEngine
{
    struct Gear
    {
        double max_rotating_speed, torque;

        Gear(double max_rotating_speed, double torque) {
            this->max_rotating_speed = max_rotating_speed;
            this->torque = torque;
        }
    };
    std::vector<Gear> gears;

    PhysicsVehicleEngine(std::vector<Gear> gears);
    double getTorque(double rotating_speed);
};

#endif // PHYSICSVEHICLEENGINE_H
