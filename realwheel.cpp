#include "realwheel.h"

RealWheel::RealWheel(Position const & p, Wheel * wheel)
    : p(p)
{
    this->wheel = wheel;
}
