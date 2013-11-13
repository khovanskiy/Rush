#include "displayobject.h"
#include "math.h"
#include "console.h"
#include "mouse.h"
#include "mouseevent.h"
#include <numeric>
#include <cmath>

DisplayObject::DisplayObject()
{
    lmatrix = new QMatrix();
    gmatrix = new QMatrix();
    _visible = true;
    _x = _y = rx = ry = _rotationZ = 0;
    _scaleX = _scaleY = 1;
    _ratio = false;
}

DisplayObject::~DisplayObject()
{
    delete lmatrix;
    delete gmatrix;
}

QMatrix* DisplayObject::getRenderMatrix()
{
    return getGlobalMatrix();
}

QMatrix* DisplayObject::getGlobalMatrix()
{
    QMatrix* r = getLocalMatrix();
    gmatrix->setMatrix(r->m11(),r->m12(),r->m21(),r->m22(),r->dx(),r->dy());
    return gmatrix;
}

QMatrix* DisplayObject::getLocalMatrix()
{
    QMatrix a; a.translate(-rx,-ry);
    QMatrix b; b.scale(_scaleX, _scaleY);
    QMatrix c; c.rotate(_rotationZ / asin(1) * 90);
    QMatrix d; d.translate(rx,ry);
    QMatrix e; e.translate(_x-rx, _y-ry);
    QMatrix r = a * b * c * d * e;
    lmatrix->setMatrix(r.m11(),r.m12(),r.m21(),r.m22(),r.dx(),r.dy());
    return lmatrix;
}

QRectF DisplayObject::getRenderBounds()
{
    return getBounds(getRenderMatrix());
}

QRectF DisplayObject::getBounds(QMatrix* p) const // Спасибо линейной алгебре!
{
    float nx = 0;
    float ny = 0;
    float x1 = std::numeric_limits<float>::max(); float y1 = std::numeric_limits<float>::max();
    float x2 = std::numeric_limits<float>::min(); float y2 = std::numeric_limits<float>::min();

    nx = p->dx();
    ny = p->dy();

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->m21() * _height + p->dx();
    ny = p->m22() * _height + p->dy();

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->m11() * _width + p->dx();
    ny = p->m12() * _width + p->dy();

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->m11() * _width + p->m21() * _height + p->dx();
    ny = p->m12() * _width + p->m22() * _height + p->dy();

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
    QMatrix* res = getRenderMatrix();
    return (float)(_height * abs(res->m12()) + _width * abs(res->m11()));
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
    QMatrix* res = getRenderMatrix();
    return (float)(_width * abs(res->m12()) + _height * abs(res->m11()));
}

bool DisplayObject::isVisible() const
{
    return _visible;
}

void DisplayObject::setRSPointCenter()
{
    rx = _width / 2;
    ry = _height / 2;
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
