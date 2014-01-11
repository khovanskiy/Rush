#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "physicsobject.h"
#include "carwheel.h"

class Obstacle : public PhysicsObject
{
    friend class PhysicsObjectFactory;

    CarWheel* wheel;
    QString obstacle_type;

    Obstacle(Shape2D* shape, double mass, double inertia_moment, QString obstacle_type);
    virtual ~Obstacle();

public:

    static const QString WOODEN_BOX;
    static const QString WOODEN_BARREL;
    static const QString STONE_WALL;

    virtual std::vector<PhysicsObject*> calculateInnerState(double dt);
    QString getObstacleType();
};

#endif // OBSTACLE_H
