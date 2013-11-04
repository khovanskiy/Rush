#ifndef REALWHEEL_H
#define REALWHEEL_H
#include "wheel.h"
#include "position.h"

struct RealWheel
{
    Position p;
    Wheel * wheel;

    RealWheel(Position const & p, Wheel * wheel);
};

#endif // REALWHEEL_H
