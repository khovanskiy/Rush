#include "vehiclefactory.h"
#include "console.h"
#include "physicsworld.h"

static const double G = 9.80665;
static const double M_PI = 3.14159265358979323846;
static const double inch_to_meter = 0.0254;

VehicleFactory::VehicleFactory()
{
}

double VehicleFactory::revsPerKmToRadius(double revsPerKilometer)
{
    return 1000 / (2 * M_PI * revsPerKilometer);
}

double VehicleFactory::tireSpecsToRadius(double tread_width,
                                         double aspect_ratio, double rim_diameter)
{
    return ((tread_width / 1000) * (aspect_ratio / 100) + rim_diameter * inch_to_meter);
}

Vehicle* VehicleFactory::createCar(double length, double width, double mass)
{
    //Console::print("Creating simple car...");
    Vehicle* result = new Vehicle(new Rectangle2D(Point2D(0, 0), width, length, 0), mass,
                   mass * (width * width + length * length) / 12);
    //Console::print("Simple car has been created.");
    PhysicsWorld::getInstance().addObject(result);
    return result;
}

Vehicle* VehicleFactory::createDodgeChallengerSRT8()
{
    //Console::print("Creating Dodge Challenger SRT8...");
    Vehicle* vehicle = createCar(5.0, 1.923, 1887);
    double r[] = {3.59, 2.19, 1.41, 1, 0.83};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    vehicle->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    CarTrack back(-1.62724, 1.604, revsPerKmToRadius(456), 0.466,
                  true, true, RotationReaction::NoRotation,
                  0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.74552, 1.603, revsPerKmToRadius(456), 0.544,
                   false, true, RotationReaction::StraightRot,
                   0.9, 0.025, 1.5, 1.5, M_PI / 6);
    vehicle->setWheels(back, front, 1.45);
    vehicle->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, vehicle->chassis.getMassCenter()));
    //Console::print("Dodge Challenger SRT8 has been created.");    
    return vehicle;
}

Vehicle* VehicleFactory::createFerrari599GTO()
{
    //Console::print("Creating Ferrari 599 GTO...");
    Vehicle* vehicle = createCar(4.710, 1.962, 1605);
    double r[] = {3.15, 2.18, 1.57, 1.19, 0.94, 0.76};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    vehicle->setEngine(VehicleEngine(620, 8400, ratios, 4.18));
    CarTrack back(-1.328, 1.610, tireSpecsToRadius(315, 35, 20),
                  0.53, true, true, RotationReaction::NoRotation,
                  0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.470, 1.701, tireSpecsToRadius(280, 35, 20),
                   0.47, false, true, RotationReaction::StraightRot,
                   0.9, 0.025, 1.5, 1.5, M_PI / 6);
    vehicle->setWheels(back, front, 1.326);
    vehicle->setVehicleBody(VehicleBody(0.356, 4.710, 1.962, 1.326, vehicle->chassis.getMassCenter()));
    //Console::print("Ferrari 599 GTO has been created.");
    return vehicle;
}
