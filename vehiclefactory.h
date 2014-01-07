#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include "vehicle.h"
#include "carwheel.h"

class VehicleFactory
{
public:
    VehicleFactory();

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
};

#endif // VEHICLEFACTORY_H
