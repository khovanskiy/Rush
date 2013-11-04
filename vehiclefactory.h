#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include "vehicle.h"

class VehicleFactory
{
public:
    VehicleFactory();
    static Vehicle createVehicle(Vector2D const & r, double angle,
                                 Vector2D const & v, double angular_speed,
                                 Vector2D const & f, double force_moment,
                                 Vector2D const & a, double angular_acceleration,
                                 double width, double length, double mass_center_height,
                                 RealBody r_body,
                                 RealEngine r_engine,
                                 std::vector<RealTurret> r_turrets,
                                 std::vector<RealWheel> r_wheels);
};

#endif // VEHICLEFACTORY_H
