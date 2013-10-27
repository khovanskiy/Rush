#include "physicsvehicleengine.h"

PhysicsVehicleEngine::PhysicsVehicleEngine(std::vector<Gear> gears)
{
    this->gears = gears;
}

double PhysicsVehicleEngine::getTorque(double rotating_speed) {
    double result = 0;
    for (std::vector<Gear>::iterator i = gears.begin(); i != gears.end(); i++) {
        if ((rotating_speed <= (*i).max_rotating_speed) && (result <= (*i).torque)) {
            result = (*i).torque;
        }
    }
    return result;
}
