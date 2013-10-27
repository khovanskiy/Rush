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

void Vector2D::setLength(double k)
{
    mul(k / getLength());
}

double Vector2D::getLength() const
{
    return sqrt(this->x * this->x + this->y * this->y);
}

void Vector2D::normalize()
{
    mul(1 / getLength());
}

void Vector2D::rotate(double alpha)
{
    double x0 = x;
    x = x * cos(alpha) - y * sin(alpha);
    y = y * cos(alpha) + x0 * sin(alpha);
}

double Vector2D::scalar(const Vector2D &a, const Vector2D &b)
{
    return a.x * b.x + a.y * b.y;
}

double Vector2D::cross(const Vector2D &a, const Vector2D &b)
{
    return a.x * b.y - b.x * a.y;
}

double Vector2D::angleBetween(const Vector2D &a, const Vector2D &b)
{
    return atan2(a.x * b.y - b.x * a.y, scalar(a,b));
}

double Vector2D::scalar(const Vector2D &other)
{
    return Vector2D::scalar(*this, other);
}

double Vector2D::cross(const Vector2D &other)
{
    return Vector2D::cross(*this, other);
}

double Vector2D::angleBetween(const Vector2D &other)
{
    return Vector2D::angleBetween(*this, other);
}

