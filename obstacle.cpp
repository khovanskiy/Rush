#include "obstacle.h"

static const double G = 9.8;
static const double rotation_friction = 3;

const int Obstacle::WOODEN_BOX = 0;
const int Obstacle::WOODEN_BARREL = 1;
const int Obstacle::STONE_WALL = 2;

Obstacle::Obstacle(Shape2D *shape, double mass, double inertia_moment, int obstacle_type)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::OBSTACLE)
{
    this->obstacle_type = obstacle_type;
}

Obstacle::~Obstacle()
{
}

void Obstacle::calculateInnerState(double dt)
{
    PhysicsObject::calculateInnerState(dt);
    double vl = v.getLength();
    if (vl != 0)
    {
        if (vl > G * dt)
        {
            f = v;
            f.setLength(-mass * G);
        }
        else
        {
            f = v;
            f.setLength(-mass * vl / dt);
        }
    }
    this->force_moment = -this->angular_speed * rotation_friction * this->inertia_moment * G;
    return;// 0;
}


int Obstacle::getObstacleType()
{
    return this->obstacle_type;
}
