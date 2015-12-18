#include "matrix.h"

#include "console.h"

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

/**
 * @brief Matrix::invert
 * @see http://en.wikipedia.org/wiki/Inverse_matrix#Methods_of_matrix_inversion
 * @return
 */
Matrix Matrix::invert()
{
    double a = M11;
    double b = M12;
    //double c = 0;
    double d = M21;
    double e = M22;
    //double f = 0;
    double g = M31;
    double h = M32;
    //double i = 1;
    //double det = a * (e * i - f * h) - b * (i * d - f * g) + c * (d * h - e * g);
    double det = a * e - b * d; //optimized
    double det1 = 1 / det;
    if (fabs(det) < 1e-32)
    {
        return Matrix();
    }
    double ki = 1 / (a * e - b * d);
    return Matrix(e * det1, -b * det1, -d * det1, a * det1, (d * h - e * g) * ki, -(a * h - b * g) * ki);//optimized
    /*double A = e * i - f * h;
    double B = -(d * i - f * g);
    double C = d * h - e * g;
    double D = -(b * i - c * h);
    double E = (a * i - c * g);
    double F = -(a * h - b * g);
    //double G = (b * f - c * e); //0
    //double H = -(a * f - c * d);//0
    //double I = (a * e - b * d); //1
    //Console::print(I);
    return Matrix(A, D, B, E, C, F);*/
}

Matrix Matrix::transformation(const Vector2D &position, const Vector2D &scaling, double rotationZ, const Vector2D &rs_point)
{
    Matrix a = Matrix::translation(Vector2D(-rs_point.x, -rs_point.y));
    Matrix b = Matrix::scaling(Vector2D(scaling.x, scaling.y));
    Matrix c = Matrix::rotationZ(rotationZ);
    Matrix d = Matrix::translation(Vector2D(rs_point.x, rs_point.y));
    Matrix e = Matrix::translation(Vector2D(position.x - rs_point.x, position.y - rs_point.y));
    a.mul(b);
    a.mul(c);
    a.mul(d);
    a.mul(e);
    return a;
}

Vector2D Matrix::map(const Vector2D& v)
{
    return Vector2D(M11 * v.x + M21 * v.y + M31, M12 * v.x + M22 * v.y + M32);
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
