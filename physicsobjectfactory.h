#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include "vehicle.h"
#include "carwheel.h"
#include "explosion.h"
#include "obstacle.h"

class PhysicsObjectFactory
{
    PhysicsObjectFactory();

    static double revsPerKmToRadius(double rotationsPerKilometer);
    static double tireSpecsToRadius(double tread_width, double aspect_ratio, double rim_diameter);

    static Vehicle* createEmptyCar(double length, double width, double mass, int vehicle_type);

public:

    static Vehicle* createVehicle(int vehicle_type);

    static Bullet* createBullet(Vector2D r, double angle, int bullet_type, double dt);

    static Turret* createVehicleTurret(int turret_type);

    static Explosion* createExplosion(Vector2D r, double angle, int explosion_type);

    static Obstacle* createObstacle(Vector2D r, double angle, int obstacle_type);
};

#endif // VEHICLEFACTORY_H
