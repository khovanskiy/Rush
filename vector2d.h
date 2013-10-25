#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D(double, double);
    Vector2D();
    void add(const Vector2D&);
    void sub(const Vector2D&);
    void mul(double k);
    void div(double k);
    void normalize();
    double getLength() const;
    double x;
    double y;
};

#endif // VECTOR2D_H
