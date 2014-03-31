#ifndef MATRIX_H
#define MATRIX_H

#include <QMatrix>

#include "vector2d.h"

class Matrix
{
public:
    Matrix();
    Matrix(double, double, double, double, double, double);
    Matrix(Matrix const&);
    Matrix& operator=(const Matrix&);
    void swap(const Matrix&);
    QMatrix toQMatrix();
    double M11;
    double M12;
    double M21;
    double M22;
    double M31;
    double M32;
    Vector2D map(const Vector2D& v);
    static Matrix translation(const Vector2D&);
    static Matrix scaling(const Vector2D&);
    static Matrix rotationZ(double);
    static Matrix mul(const Matrix &, const Matrix&);
    void mul(const Matrix&);
    Matrix invert();
};

#endif // MATRIX_H
