#include "transformableobject.h"

#include "console.h"

TransformableObject::TransformableObject()
{
    scaling.x = scaling.y = 1;
    rotationZ = 0;
    isWHsettedup = false;
}

TransformableObject::~TransformableObject()
{

}

void TransformableObject::setSize(const Vector2D &size)
{
    outer_size = size;
    isWHsettedup = true;
}

const Vector2D& TransformableObject::getSize() const
{
    if (isWHsettedup)
    {
        return outer_size;
    }
    return inner_size;
}

void TransformableObject::setPosition(const Vector2D &p)
{
    position.x = p.x;
    position.y = p.y;
}

const Vector2D& TransformableObject::getPosition() const
{
    return position;
}

void TransformableObject::setRSPointCenter()
{
    rs_point.x = 0.5;
    rs_point.y = 0.5;
}

void TransformableObject::setRSPoint(const Vector2D &m)
{
    rs_point = m;
}

QRectF TransformableObject::getBounds(const Matrix& p)
{
    float nx = 0;
    float ny = 0;
    float x1 = std::numeric_limits<float>::max(); float y1 = std::numeric_limits<float>::max();
    float x2 = std::numeric_limits<float>::min(); float y2 = std::numeric_limits<float>::min();

    nx = p.M31;
    ny = p.M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p.M21 * inner_size.y + p.M31;
    ny = p.M22 * inner_size.y + p.M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p.M11 * inner_size.x + p.M31;
    ny = p.M12 * inner_size.x + p.M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p.M11 * inner_size.x + p.M21 * inner_size.y + p.M31;
    ny = p.M12 * inner_size.x + p.M22 * inner_size.y + p.M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    return QRectF(x1, y1, x2 - x1, y2 - y1);
}

Matrix& TransformableObject::getTransform()
{
    float kx = 1;
    float ky = 1;
    if (isWHsettedup)
    {
        kx = outer_size.x / inner_size.x;
        ky = outer_size.y / inner_size.y;
    }
    Matrix a = Matrix::translation(Vector2D(-rs_point.x * inner_size.x, -rs_point.y * inner_size.y));
    Matrix b = Matrix::rotationZ(rotationZ);
    Matrix c = Matrix::scaling(Vector2D(scaling.x * kx, scaling.y * ky));

    Matrix d = Matrix::translation(Vector2D(position.x, position.y));

    /*Matrix a = Matrix::translation(Vector2D(-position.x, -position.y));
    Matrix b = Matrix::rotationZ(rotationZ);
    Matrix c = Matrix::scaling(Vector2D(scaling.x * kx, scaling.y * ky));
    Matrix d = Matrix::translation(Vector2D(position.x - rs_point.x * inner_size.x, position.y - rs_point.y * inner_size.y));*/

    a.mul(b);
    a.mul(c);
    a.mul(d);
    matrix = a;
    return matrix;
}
