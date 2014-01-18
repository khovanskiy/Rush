#include "physicsobjectfactory.h"
#include "console.h"
#include "physicsworld.h"

static const double G = 9.80665;
static const double M_PI = 3.14159265358979323846;
static const double inch_to_meter = 0.0254;

PhysicsObjectFactory::PhysicsObjectFactory()
{
}

double PhysicsObjectFactory::revsPerKmToRadius(double revsPerKilometer)
{
    return 1000 / (2 * M_PI * revsPerKilometer);
}

double PhysicsObjectFactory::tireSpecsToRadius(double tread_width,
                                         double aspect_ratio, double rim_diameter)
{
    return ((tread_width / 1000) * (aspect_ratio / 100) + rim_diameter * inch_to_meter);
}

Vehicle* PhysicsObjectFactory::createEmptyCar(double length, double width, double mass, int vehicle_type)
{
    return new Vehicle(new Rectangle2D(Point2D(0, 0), width, length, 0), mass,
                   mass * (width * width + length * length) / 12, vehicle_type);
}


Vehicle* PhysicsObjectFactory::createVehicle(int vehicle_type)
{
    Vehicle* result;
    if (vehicle_type == Vehicle::DODGE_CHALLENGER_SRT8)
    {
        result = createEmptyCar(5.0, 1.923, 1887, vehicle_type);
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
    else if (vehicle_type == Vehicle::FERRARI_599GTO)
    {
        result = createEmptyCar(4.710, 1.962, 1605, vehicle_type);
        double r[] = {3.15, 2.18, 1.57, 1.19, 0.94, 0.76};
        std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
        result->setEngine(VehicleEngine(620, 8400, ratios, 4.18));
        CarTrack back(-1.328, 1.610, tireSpecsToRadius(315, 35, 20),
                      0.53, true, true, RotationReaction::NoRotation,
                      0.9, 0.025, 0.9, 1.5, M_PI / 6);
        CarTrack front(1.470, 1.701, tireSpecsToRadius(280, 35, 20),
                       0.47, false, true, RotationReaction::StraightRot,
                       0.9, 0.025, 0.9, 1.5, M_PI / 6);
        result->setWheels(back, front, 1.326);
        result->setVehicleBody(VehicleBody(0.356, 4.710, 1.962, 1.326, result->chassis.getMassCenter()));
    }
    PhysicsWorld::gi().addObject(result);
    return result;
}

Bullet* PhysicsObjectFactory::createBullet(Vector2D r, double angle, int bullet_type, double dt)
{
    double width, height, mass, speed, time_to_live;
    if (bullet_type == Bullet::BULLET)
    {
        width = 0.15;
        height = 0.43;
        mass = 1;
        speed = 50;
        time_to_live = 3;
    }
    else if (bullet_type == Bullet::CUT)
    {
        width = 0.03;
        height = 0.03;
        mass = 0.00001;
        speed = 12;
        time_to_live = 0.05;
    }
    else if (bullet_type == Bullet::MISSILE)
    {
        width = 0.5;
        height = 1.9;
        mass = 100;
        speed = 40;
        time_to_live = 3;
    }
    Vector2D v(0, speed);
    v.rotate(angle);
    return new Bullet(r, v, mass, bullet_type, width, height, dt, time_to_live);
}

Turret* PhysicsObjectFactory::createVehicleTurret(int turret_type)
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
}

Explosion* PhysicsObjectFactory::createExplosion(Vector2D r, double angle, int explosion_type)
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
}

Obstacle* PhysicsObjectFactory::createObstacle(Vector2D r, double angle, int obstacle_type)
{
    Shape2D * shape;
    double mass = 100, inertia_moment = 50;
    bool dynamic;
    if (obstacle_type == Obstacle::STONE_WALL)
    {
        shape = new Rectangle2D(r, 2, 0.5, angle);
        mass = 10000;
        inertia_moment = 1000;
        dynamic = false;
    }
    else if (obstacle_type == Obstacle::WOODEN_BOX)
    {
        shape = new Rectangle2D(r, 1, 1, angle);
        mass = 30;
        inertia_moment = 6;
        dynamic = true;
    }
    else if (obstacle_type == Obstacle::WOODEN_BARREL)
    {
        shape = new Circle2D(r, 1, angle);
        mass = 100;
        inertia_moment = 50;
        dynamic = true;
    }
    Obstacle* result = new Obstacle(shape, mass, inertia_moment, obstacle_type);
    if (!dynamic)
    {
        result->setStatic();
    }
    PhysicsWorld::gi().addObject(result);
    return result;
}
