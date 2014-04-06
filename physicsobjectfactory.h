#ifndef PHYSICSOBJECTFACTORY_H
#define PHYSICSOBJECTFACTORY_H

#include "vehicle.h"

class PhysicsObjectFactory
{
    static double revsPerKmToRadius(double rotationsPerKilometer);
    static double tireSpecsToRadius(double tread_width, double aspect_ratio, double rim_diameter);
    static double inchToMeter(double inches);

    //static Vehicle* createEmptyCar(double length, double width, double width_with_mirrors, double mass, int vehicle_type);

public:

    static Vehicle* createVehicle(int id_object, int vehicle_type);
    static Turret* createTurret(int id_object, int turret_type);
    static Bullet* createBullet(int id_object, Vector2D r, double angle, int bullet_type, double dt);

    //static Turret* createVehicleTurret(int turret_type);

    //static Explosion* createExplosion(Vector2D r, double angle, int explosion_type);

    //static Obstacle* createObstacle(Vector2D r, double angle, int obstacle_type);
};

#endif // PHYSICSOBJECTFACTORY_H
