#include "displayobject.h"
#include "math.h"
#include "console.h"
#include "mouse.h"
#include "mouseevent.h"
#include <numeric>
#include <cmath>

DisplayObject::DisplayObject()
{
    lmatrix = new Matrix();
    gmatrix = new Matrix();
    _visible = true;
    _x = _y = rx = ry = _rotationZ = 0;
    _scaleX = _scaleY = 1;
    _ratio = false;
    root = 0;
}

DisplayObject::~DisplayObject()
{
    delete lmatrix;
    delete gmatrix;
}

void DisplayObject::render(QPainter *, const Matrix &base)
{

}

Matrix* DisplayObject::getRenderMatrix()
{
    return getGlobalMatrix();
}

Matrix* DisplayObject::getGlobalMatrix()
{
    if (false)
    {
        *gmatrix = Matrix::mul(*getLocalMatrix(), *root->getLocalMatrix());
    }
    else
    {
        *gmatrix = *getLocalMatrix();
    }
    return gmatrix;
}

Matrix* DisplayObject::getLocalMatrix()
{
    Matrix a = Matrix::translation(Vector2D(-rx, -ry));
    Matrix b = Matrix::scaling(Vector2D(_scaleX, _scaleY));
    Matrix c = Matrix::rotationZ(-_rotationZ);
    Matrix d = Matrix::translation(Vector2D(rx, ry));
    Matrix e = Matrix::translation(Vector2D(_x - rx, _y - ry));
    a.mul(b);
    a.mul(c);
    a.mul(d);
    a.mul(e);
    *lmatrix = a;
    return lmatrix;
}

QRectF DisplayObject::getRenderBounds()
{
    return getBounds(getRenderMatrix());
}

QRectF DisplayObject::getBounds(Matrix* p) const // Спасибо линейной алгебре!
{
    float nx = 0;
    float ny = 0;
    float x1 = std::numeric_limits<float>::max(); float y1 = std::numeric_limits<float>::max();
    float x2 = std::numeric_limits<float>::min(); float y2 = std::numeric_limits<float>::min();

    nx = p->M31;
    ny = p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->M21 * _height + p->M31;
    ny = p->M22 * _height + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->M11 * _width + p->M31;
    ny = p->M12 * _width + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->M11 * _width + p->M21 * _height + p->M31;
    ny = p->M12 * _width + p->M22 * _height + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    return QRectF(x1, y1, x2 - x1, y2 - y1);
}

void DisplayObject::setWidth(float value)
{
    setScaleX(value / _width);
    if (isRatio())
    {
        setScaleY(getScaleX());
    }
}

float DisplayObject::getWidth()
{
    Matrix* res = getRenderMatrix();
    return (float)(_height * abs(res->M12) + _width * abs(res->M11));
}

void DisplayObject::setHeight(float value)
{
    setScaleY(value / _height);
    if (isRatio())
    {
        setScaleX(getScaleY());
    }
}

float DisplayObject::getHeight()
{
    Matrix* res = getRenderMatrix();
    return (float)(_width * abs(res->M12) + _height * abs(res->M11));
}

bool DisplayObject::isVisible() const
{
    return _visible;
}

void DisplayObject::setRSPointCenter()
{
    setRSPoint(Vector2D(0.5, 0.5));
}

void DisplayObject::setRSPoint(const Vector2D &c)
{
    rx = _width * c.x;
    ry = _height * c.y;
}

bool DisplayObject::hitTestPoint(float x, float y)
{
    QRectF r = getRenderBounds();
    return (r.top() <= y && y <= r.bottom() && r.left() <= x && x <= r.right());
}

QString DisplayObject::h(int k, QString text)
{
    QString temp = "";
    for (int i = 0; i < k; i++)
    {
        temp.append(" ");
    }
    temp.append(text);
    return temp;
}
