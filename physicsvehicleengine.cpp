#include "physicsvehicleengine.h"
#define M_PI	 3.14159265358979323846

PhysicsVehicleEngine::PhysicsVehicleEngine(std::vector<Gear> gears)
    : gears(gears)
{
    setRotations(0);
}

void PhysicsVehicleEngine::setRotations(double rotating_speed) {
    spins_per_minute = 60 * rotating_speed / (2 * M_PI);
    current_torque = 0;
    current_gear = 0;
    for (std::vector<Gear>::iterator i = gears.begin(); i != gears.end(); i++) {
        if ((rotating_speed <= (*i).max_rotating_speed) && (current_torque <= (*i).torque)) {
            current_torque = (*i).torque;
            current_gear = (*i).number;
        }
    }    
}

double PhysicsVehicleEngine::getSpins()
{
    return spins_per_minute;
}

double PhysicsVehicleEngine::getTorque(double percent)
{
    return current_torque * percent;
}

int PhysicsVehicleEngine::getGear()
{
    return current_gear;
}
