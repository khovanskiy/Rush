#include "box.h"

Box::Box(const Vector2D &r, double angle,
         const Vector2D &v, double angular_speed,
         const Vector2D &f, double force_moment,
         const Vector2D &a, double angular_acceleration,
         double mass, double width, double length)
    : Shape(r, angle, v, angular_speed, f, force_moment,
            a, angular_acceleration, mass, mass * (width * width + length * length) / 12,
            Vector2D(0, 0))
{
}
