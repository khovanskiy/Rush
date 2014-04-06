#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "physicsobject.h"
#include "carwheel.h"

class Obstacle : public PhysicsObject
{
    friend class PhysicsObjectFactory;

    int obstacle_type;

    Obstacle(int id, Shape2D* shape, double mass, double inertia_moment, int obstacle_type);
    virtual ~Obstacle();

public:

    static const int WOODEN_BOX;
    static const int WOODEN_BARREL;
    static const int STONE_WALL;

    virtual void calculateInnerState(double dt);
    int getObstacleType();
};

#endif // OBSTACLE_H
