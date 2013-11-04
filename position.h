#ifndef POSITION_H
#define POSITION_H
#include "vector2d.h"

struct Position
{
    Vector2D r;
    double mass;

    Position(Vector2D const & r, double mass);
    Position(Position const & p);
};

#endif // POSITION_H
