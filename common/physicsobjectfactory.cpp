#include "physicsobjectfactory.h"
#include "console.h"
#include "obstacle.h"

static const double G = 9.80665;
//static const double M_PI = 3.14159265358979323846;
static const double inch_to_meter = 0.0254;

double PhysicsObjectFactory::revsPerKmToRadius(double revsPerKilometer)
{
    return 1000 / (2 * M_PI * revsPerKilometer);
}

double PhysicsObjectFactory::tireSpecsToRadius(double tread_width,
                                         double aspect_ratio, double rim_diameter)
{
    return ((tread_width / 1000) * (aspect_ratio / 100) + rim_diameter * inch_to_meter);
}

double PhysicsObjectFactory::inchToMeter(double inches)
{
    return inches * 0.0254;
}

/*Vehicle* PhysicsObjectFactory::createEmptyCar(double length, double width, double width_with_mirrors,
                                              double mass, int vehicle_type)

{
    return new Vehicle(new Rectangle2D(Point2D(0, 0), width, length, 0), width_with_mirrors,
                       mass, mass * (width * width + length * length) / 12, vehicle_type);
}*/


Vehicle* PhysicsObjectFactory::createVehicle(int id_object, int vehicle_type)
{
    Vehicle* result;
    if (vehicle_type == 0)//Vehicle::DODGE_CHALLENGER_SRT8)
    {
        result = new Vehicle(id_object, new Rectangle2D(Point2D(0, 0), 1.923, 5.0), 2270);
        result->type_object = result->vehicle_type = vehicle_type;
        double r[] = {3.59, 2.19, 1.41, 1, 0.83};
        std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
        result->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
        CarTrack back(-1.62724, 1.604, revsPerKmToRadius(456), 0.466,
                      true, true, RotationReaction::NoRotation,
                      0.9, 0.025, 1.5, 1.5, M_PI / 6);
        CarTrack front(1.74552, 1.603, revsPerKmToRadius(456), 0.544,
                       false, true, RotationReaction::StraightRot,
                       0.9, 0.025, 1.5, 1.5, M_PI / 6);
        result->setWheels(back, front, 1.45);
        result->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, result->chassis.getMassCenter()));
    }
    else if (vehicle_type == 1)//Vehicle::FERRARI_599GTO)
    {
        result = new Vehicle(id_object, new Rectangle2D(Point2D(0, 0), 1.962, 4.710), 1605);
        result->type_object = result->vehicle_type = vehicle_type;
        double r[] = {3.15, 2.18, 1.57, 1.19, 0.94, 0.76};
        std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
        result->setEngine(VehicleEngine(620, 8400, ratios, 4.18));
        CarTrack back (-1.328, 1.610, tireSpecsToRadius(315, 35, 20),
                      0.53, true, true, RotationReaction::NoRotation,
                      0.9, 0.025, 0.9, 1.5, M_PI / 6);
        CarTrack front(1.470, 1.701, tireSpecsToRadius(280, 35, 20),
                       0.47, false, true, RotationReaction::StraightRot,
                       0.9, 0.025, 0.9, 1.5, M_PI / 6);
        result->setWheels(back, front, 1.326);
        result->setVehicleBody(VehicleBody(0.356, 4.710, 1.962, 1.326, result->chassis.getMassCenter()));
    }
    else if (vehicle_type == 2)//Vehicle::FORD_F150_SVT_RAPTOR)
    {
        /*result = createEmptyCar(inchToMeter(232.1), inchToMeter(86.3),
                                inchToMeter(104.1), 2813, vehicle_type);*/
        result = new Vehicle(id_object, new Rectangle2D(Point2D(0, 0), inchToMeter(100), inchToMeter(232.1)), 2813);
        result->type_object = result->vehicle_type = vehicle_type;
        double r[] = {4.17, 2.34, 1.52, 1.14, 0.86, 0.69};
        std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
        result->setEngine(VehicleEngine(1001, 7000, ratios, 4.10));
        //http://en.wikipedia.org/wiki/Ford_Boss_engine#7.0.C2.A0L
        CarTrack back (-inchToMeter(67.2), inchToMeter(73.6), tireSpecsToRadius(315, 35, 20),
                      0.43, true, true, RotationReaction::NoRotation,
                      0.9, 0.025, 0.9, 1.5, M_PI / 6);
        CarTrack front(inchToMeter(78), inchToMeter(73.6), tireSpecsToRadius(280, 35, 20),
                       0.57, true, true, RotationReaction::StraightRot,
                       0.9, 0.025, 0.9, 1.5, M_PI / 6);
        result->setWheels(back, front, inchToMeter(78.4));
        result->setVehicleBody(VehicleBody(0.356, inchToMeter(232.1), inchToMeter(86.3),
                                           inchToMeter(78.4), result->chassis.getMassCenter()));
    }
    result->setTorquePercent(1);
    return result;
}

Turret* PhysicsObjectFactory::createTurret(int id_object, int turret_type)
{
    Turret* result;

    switch (turret_type)
    {
    case 0:
    {
        result = new Turret(id_object, new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 100, 0.2, asin(1), Bullet::BULLET, 0);
        result->type_object = result->turret_type = turret_type;
    } break;
    case 1:
    {
        result = new Turret(id_object, new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 150, 0.5, asin(1), Bullet::MISSILE, 0);
        result->type_object = result->turret_type = turret_type;
    } break;
    case 2:
    {
        result = new Turret(id_object, new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 200, 1.5, asin(1), 2, 0);
        result->type_object = result->turret_type = turret_type;
    } break;
    }


    return result;
}

Bullet* PhysicsObjectFactory::createBullet(int id_object, const Vector2D& r, const Vector2D& v, int bullet_type, double dt)
{
    double width, height, mass, speed, time_to_live, damage;
    if (bullet_type == Bullet::BULLET)
    {
        width = 0.1;
        height = 0.43;
        mass = 5;
        speed = 70;
        time_to_live = 3;
        damage = 7;
    }
    else if (bullet_type == Bullet::MISSILE)
    {
        width = 0.5;
        height = 1.9;
        mass = 100;
        speed = 40;
        time_to_live = 3;
        damage = 35;
    }
    else if (bullet_type == 2)
    {
        width = 1;
        height = 1;
        mass = 500;
        speed = 30;
        time_to_live = 3;
        damage = 95;
    }
    Vector2D va = v;
    va.normalize();
    va.mul(speed);
    Bullet* bullet = new Bullet(id_object, r, va, mass, bullet_type, width, height, dt, time_to_live);
    bullet->type_object = bullet_type;
    bullet->setDamage(damage);
    return bullet;
}

Obstacle* PhysicsObjectFactory::createObstacle(int id_object, int obstacle_type)
{
    Shape2D * shape;
    double mass = 100, inertia_moment = 50;
    bool dynamic;
    if (obstacle_type == 0)
    {
        shape = new Rectangle2D(Vector2D(0, 0), 200, 10);
        mass = 1000000;
        inertia_moment = 1000000;
        dynamic = false;
    }
    else if (obstacle_type == 1)
    {
        shape = new Rectangle2D(Vector2D(0, 0), 1, 1);
        mass = 30;
        inertia_moment = 6;
        dynamic = true;
    }
    else if (obstacle_type == 2)
    {
        shape = new Circle2D(Vector2D(0, 0), 1, 0);
        mass = 100;
        inertia_moment = 50;
        dynamic = true;
    }
    else if (obstacle_type == 3)
    {
        shape = new Circle2D(Vector2D(0, 0), 2, 0);
        mass = 1000000;
        inertia_moment = 1000000;
        dynamic = false;
    }
    Obstacle* result = new Obstacle(id_object, shape, mass, inertia_moment, obstacle_type);
    result->type_object = obstacle_type;
    if (!dynamic)
    {
        result->setStatic();
    }
    return result;
}

/*Turret* PhysicsObjectFactory::createVehicleTurret(int turret_type)
{
    double width, height, max_angle;
    double fire_delay = 0.4, mass = 100, inertia_moment = 7, scatter = 0;
    int bullet_type = Bullet::BULLET;
    if (turret_type == Turret::MACHINEGUN)
    {
        bullet_type = Bullet::BULLET;
        fire_delay = 0.1;
        max_angle = 2 * asin(1);
        width = 1.09;
        height = 1.5;
        mass = 100;
        inertia_moment = 7;
        scatter = 0.1;
    }
    else if (turret_type == Turret::ROCKET_LAUNCHER)
    {
        bullet_type = Bullet::MISSILE;
        fire_delay = 2;
        max_angle = 2 * asin(1);
        width = 1.3;
        height = 2.10;
        mass = 150;
        inertia_moment = 10;
        scatter = 0;
    }
    else if (turret_type == Turret::SAW)
    {
        bullet_type = Bullet::CUT;
        fire_delay = 0.05;
        max_angle = 0;
        width = 1;
        height = 1;
        mass = 40;
        inertia_moment = 4;
        scatter = 0;
    }
    Shape2D* shape = new Rectangle2D(Point2D(0, 0), width, height, 0);
    Turret* result = new Turret(shape, mass, inertia_moment, fire_delay, max_angle, bullet_type, scatter);
    result->setStatic();
    result->turret_type = turret_type;
    return result;
}*/

/*Explosion* PhysicsObjectFactory::createExplosion(Vector2D r, double angle, int explosion_type)
{
    double start_radius, end_radius, time, explosion_impulse;
    if (explosion_type == Explosion::SMALL)
    {
        start_radius = 0.1;
        end_radius = 1;
        time = 0.05;
        explosion_impulse = 200;
    }
    else if (explosion_type == Explosion::MEDIUM)
    {
        start_radius = 0.2;
        end_radius = 3;
        time = 0.1;
        explosion_impulse = 600;
    }
    else if (explosion_type == Explosion::LARGE)
    {
        start_radius = 0.5;
        end_radius = 10;
        time = 0.2;
        explosion_impulse = 2000;
    }
    Shape2D* shape = new Circle2D(r, start_radius, angle);
    Explosion* result = new Explosion(shape, 1e10, 1e10, start_radius, end_radius,
                                      time, explosion_impulse, explosion_type);
    result->setStatic();
    return result;
}*/
