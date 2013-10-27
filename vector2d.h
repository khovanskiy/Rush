#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D(double, double);
    Vector2D();
    Vector2D(Vector2D const&);
    Vector2D& operator=(const Vector2D&);
    void swap(const Vector2D&);

    static double scalar(const Vector2D&, const Vector2D&);
    static double cross(const Vector2D &, const Vector2D&);
    static double angleBetween(const Vector2D&, const Vector2D&);

    void add(const Vector2D&);
    void sub(const Vector2D&);
    void mul(double k);
    void div(double k);
    void normalize();
    void setLength(double k);
    void rotate(double alpha);
    double getLength() const;
    double scalar(const Vector2D &);
    double cross(const Vector2D &);
    double angleBetween(const Vector2D &);

    double x;
    double y;
};

#endif // VECTOR2D_H
