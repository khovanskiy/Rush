#include "vector2d.h"
#include "math.h"

Vector2D::Vector2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D()
{
    this->x = 0;
    this->y = 0;
}

void Vector2D::add(const Vector2D &other)
{
    this->x += other.x;
    this->y += other.y;
}

void Vector2D::sub(const Vector2D &other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2D::mul(double k)
{
    this->x *= k;
    this->y *= k;
}

double Vector2D::getLength() const
{
    return sqrt(this->x * this->x + this->y * this->y);
}

void Vector2D::normalize()
{
    mul(getLength());
}


