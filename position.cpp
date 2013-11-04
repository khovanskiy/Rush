#include "position.h"

Position::Position(Vector2D const & r, double mass)
{
    this->r = r;
    this->mass = mass;
}

Position::Position(const Position &p)
{
    this->r = p.r;
    this->mass = p.mass;
}
