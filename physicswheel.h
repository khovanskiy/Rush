#ifndef PHYSICSWHEEL_H
#define PHYSICSWHEEL_H
#include "physicsobject.h"

class PhysicsWheel : public PhysicsObject
{
public:
    double muParallelFriction, muParallelRoll, muPerpendicularFriction, distributedMass,
    PhysicsWheel();
};

#endif // PHYSICSWHEEL_H
