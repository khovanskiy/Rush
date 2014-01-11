#include "obstacle.h"

static const double G = 9.80665;
static const double rotation_friction = 1;

const QString Obstacle::WOODEN_BOX = "wooden_box";
const QString Obstacle::WOODEN_BARREL = "wooden_barrel";
const QString Obstacle::STONE_WALL = "stone_wall";

Obstacle::Obstacle(Shape2D *shape, double mass, double inertia_moment, QString obstacle_type)
    : PhysicsObject(shape, mass, inertia_moment, PhysicsObject::OBSTACLE)
{
    wheel = new CarWheel(10, 10, 10, 10, 0, Vector2D(0, 0), 1, false, true, RotationReaction::NoRotation);
    wheel->distributed_weight = G * mass;
    wheel->changeState(AccelerationState::NoAcc, 0);
    wheel->distributed_torque = 0;
    this->obstacle_type = obstacle_type;
}

Obstacle::~Obstacle()
{
    delete wheel;
}

std::vector<PhysicsObject*> Obstacle::calculateInnerState(double dt)
{
    PhysicsObject::calculateInnerState(dt);
    wheel->v = this->v;
    wheel->calculateForces(dt);
    this->f = wheel->f;
    this->force_moment = wheel->force_moment - this->angular_speed * rotation_friction * this->inertia_moment * G;
    return std::vector<PhysicsObject*>();
}


QString Obstacle::getObstacleType()
{
    return this->obstacle_type;
}
