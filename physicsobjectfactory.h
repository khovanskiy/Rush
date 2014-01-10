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

    static Vehicle* createEmptyCar(double length, double width, double mass, QString vehicle_type);

public:

    static Vehicle* createVehicle(QString vehicle_type);

    static Bullet* createBullet(Vector2D r, double angle, QString bullet_type, double dt);

    static Turret* createVehicleTurret(QString turret_type);

    static Explosion* createExplosion(Vector2D r, double angle, QString explosion_type);

    static Obstacle* createObstacle(Vector2D r, double angle, QString obstacle_type);
};

#endif // VEHICLEFACTORY_H
