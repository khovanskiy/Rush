#ifndef PHYSICSVEHICLEENGINE_H
#define PHYSICSVEHICLEENGINE_H
#include <vector>

class VehicleEngine
{
    struct Gear
    {
        int number;
        double max_rotating_speed, torque;

        Gear(double max_rotating_speed, double torque, int number)
        {
            this->max_rotating_speed = max_rotating_speed;
            this->torque = torque;
            this->number = number;
        }
    };

    std::vector<Gear> gears;

    double spins_per_minute;
    int current_gear;
    double current_torque;

public:
    VehicleEngine(std::vector<Gear> const & gears);
    VehicleEngine(VehicleEngine const & engine);
    void setRotations(double rotating_speed);
    double getTorque(double percent = 1);
    double getSpins();
    int getGear();
};

#endif // PHYSICSVEHICLEENGINE_H
