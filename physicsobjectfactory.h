#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include "vehicle.h"
#include "carwheel.h"
#include "explosion.h"

class PhysicsObjectFactory
{
public:
    PhysicsObjectFactory();

    static double revsPerKmToRadius(double rotationsPerKilometer);
    static double tireSpecsToRadius(double tread_width, double aspect_ratio, double rim_diameter);

    static Vehicle* createCar(double length, double width,
                             double mass, double heigth,
                             double mu_parallel_friction, double mu_parallel_roll,
                             double mu_perpendicular_friction, double mu_broken_friction,
                             double max_angle,
                             CarTrack back, CarTrack front,
                             double air_resistance_koef);
    static Vehicle* createCar(double length, double width, double mass);
    static Vehicle* createDodgeChallengerSRT8();
    static Vehicle* createFerrari599GTO();

    static Bullet* createBullet(Vector2D r, double angle, QString bullet_type, double dt);

    static Turret* createVehicleTurret(QString turret_type);

    static Explosion* createExplosion(Vector2D r, double angle, QString explosion_type);
};

#endif // VEHICLEFACTORY_H
