#include "matrix.h"

#include "vector2d.h"
#include "math.h"

Matrix::Matrix()
{
    this->M11 = 1;
    this->M12 = 0;
    this->M21 = 0;
    this->M22 = 1;
    this->M31 = 0;
    this->M32 = 0;
}

Matrix::Matrix(double M11, double M12, double M21, double M22, double M31, double M32)
{
    this->M11 = M11;
    this->M12 = M12;
    this->M21 = M21;
    this->M22 = M22;
    this->M31 = M31;
    this->M32 = M32;
}

Matrix::Matrix(Matrix const &other)
{
    swap(other);
}

Matrix& Matrix::operator=(const Matrix &other)
{
    swap(other);
    return *this;
}

void Matrix::swap(const Matrix &other)
{
    this->M11 = other.M11;
    this->M12 = other.M12;
    this->M21 = other.M21;
    this->M22 = other.M22;
    this->M31 = other.M31;
    this->M32 = other.M32;
}

QMatrix Matrix::toQMatrix()
{
    return QMatrix(M11, M12, M21, M22, M31, M32);
}

Matrix Matrix::translation(const Vector2D &v)
{
    return Matrix(1, 0, 0, 1, v.x, v.y);
}

Matrix Matrix::scaling(const Vector2D &v)
{
    return Matrix(v.x, 0, 0, v.y, 0, 0);
}

Matrix Matrix::rotationZ(double angle)
{
    double cosa = cos(angle);
    double sina = sin(angle);
    return Matrix(cosa, sina, -sina, cosa, 0, 0);
}

Matrix Matrix::mul(const Matrix &a, const Matrix &b)
{
    double M11 = a.M11 * b.M11 + a.M12 * b.M21;
    double M12 = a.M11 * b.M12 + a.M12 * b.M22;
    double M21 = a.M21 * b.M11 + a.M22 * b.M21;
    double M22 = a.M21 * b.M12 + a.M22 * b.M22;
    double M31 = a.M31 * b.M11 + a.M32 * b.M21 + b.M31;
    double M32 = a.M31 * b.M12 + a.M32 * b.M22 + b.M32;
    return Matrix(M11, M12, M21, M22, M31, M32);
}

void Matrix::mul(const Matrix& other)
{
    swap(Matrix::mul(*this, other));
}
