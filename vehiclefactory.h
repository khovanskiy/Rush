#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include "vehicle.h"
#include "carwheel.h"

class VehicleFactory
{
public:
    VehicleFactory();
    static Vehicle* createVehicle(Vector2D const & r, double angle,
                                 Vector2D const & v, double angular_speed,
                                 Vector2D const & f, double force_moment,
                                 Vector2D const & a, double angular_acceleration,
                                 double width, double length, double mass_center_height,
                                 RealBody const & r_body,
                                 RealEngine const & r_engine,
                                 std::vector<RealTurret> const & r_turrets,
                                 std::vector<RealWheel> const & r_wheels);

    static double revsPerKmToRadius(double rotationsPerKilometer);
    static double tireSpecsToRadius(double tread_width, double aspect_ratio, double rim_diameter);

    struct CarTrack {
        double y;
        double width;
        double wheel_radius;
        bool driving;
        RotationReaction reaction;

        double weigth_percent;

        CarTrack(double y, double width, double wheel_radius, double weight_percent,
                 bool driving, RotationReaction reaction)
        {
            this->y = y;
            this->width = width;
            this->wheel_radius = wheel_radius;
            this->weigth_percent = weight_percent;
            this->driving = driving;
            this->reaction = reaction;
        }
    };

    static Vehicle* createCar(Vector2D const & r, double angle,
                             Vector2D const & v, double angular_speed,
                             double length, double width,
                             double mass, double heigth,
                             double mu_parallel_friction, double mu_parallel_roll,
                             double mu_perpendicular_friction, double mu_broken_friction,
                             double max_angle,
                             CarTrack back, CarTrack front,
                             double air_resistance_koef,
                             double max_engine_torque,
                             double max_engine_spins_per_minute,
                             std::vector<double> gear_ratios,
                             double final_ratio,
                             std::vector<RealTurret> turrets);

    static Vehicle* createDodgeChallengerSRT8(Vector2D const & r, double angle,
                                   Vector2D const & v, double angular_speed);
    static Vehicle* createFerrari599GTO(Vector2D const & r, double angle,
                                   Vector2D const & v, double angular_speed);
};

#endif // VEHICLEFACTORY_H
