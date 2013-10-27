#include "physicschassis.h"

PhysicsChassis::PhysicsChassis(std::vector<PhysicsWheel> wheels, PhysicsVehicleEngine engine)
    : wheels(wheels), engine(engine)
{
}
