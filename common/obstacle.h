#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "physicsobject.h"

class Obstacle : public PhysicsObject
{
public:
    Obstacle(int id, Shape2D* shape, double mass, double inertia_moment, int obstacle_type);
    virtual ~Obstacle();

    int obstacle_type;
    static const int WOODEN_BOX;
    static const int WOODEN_BARREL;
    static const int STONE_WALL;

    virtual void calculateInnerState(double dt);
    int getObstacleType();
    GameObjectType getFamilyId();
};

#endif // OBSTACLE_H
