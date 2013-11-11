#include "vehicleengine.h"

static const double M_PI = 3.14159265358979323846;

VehicleEngine::VehicleEngine(std::vector<Gear> const & gears)
    : gears(gears)
{
    setRotations(0);
}

VehicleEngine::VehicleEngine(VehicleEngine const & engine)
    : gears(engine.gears)
{
    setRotations(0);
}

void VehicleEngine::setRotations(double rotating_speed) {
    spins_per_minute = 60 * rotating_speed / (2 * M_PI);
    current_torque = 0;
    current_gear = 0;
    for (std::vector<Gear>::iterator i = gears.begin(); i != gears.end(); i++) {
        if ((rotating_speed <= (*i).max_rotating_speed) && (current_torque <= (*i).torque)) {
            current_torque = (*i).torque;
            current_gear = (*i).number;
            spins_per_minute *= (*i).ratio;
        }
    }    
}

double VehicleEngine::getSpins()
{
    return spins_per_minute;
}

double VehicleEngine::getTorque(double percent)
{
    return current_torque * percent;
}

int VehicleEngine::getGear()
{
    return current_gear;
}
