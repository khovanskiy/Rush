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

    prev_x = current_x = target_x = 0;
    prev_y = current_y = target_y = 0;

    rx = ry = 0;

    inner_width = inner_height = 1;

    outer_width = outer_height = 1;

    isWHsettedup = false;

    speed_rotationZ = prev_rotationZ = current_rotationZ = target_rotationZ = 0;

    prev_scaleX = current_scaleX = target_scaleX = 1;
    prev_scaleY = target_scaleY = current_scaleY = 1;

    _ratio = false;
    root = 0;
    ready = false;

    isInt = false;
}

DisplayObject::~DisplayObject()
{
    delete lmatrix;
    delete gmatrix;
}

void DisplayObject::render(QPainter *, const Matrix &base, bool new_frame, float interpolation)
{
    if (isInt)
    {
        if (new_frame)
        {
            prev_x = target_x;
            prev_y = target_y;
            prev_scaleX = target_scaleX;
            prev_scaleY = target_scaleY;
            prev_rotationZ = target_rotationZ;
        }
        current_rotationZ = prev_rotationZ + (target_rotationZ - prev_rotationZ) * interpolation;

        current_x = prev_x + (target_x - prev_x) * interpolation;
        current_y = prev_y + (target_y - prev_y) * interpolation;
        current_scaleX = prev_scaleX + (target_scaleX - prev_scaleX) * interpolation;
        current_scaleY = prev_scaleY + (target_scaleY - prev_scaleY) * interpolation;
        /*if (abs(current_x - target_x) <= 10e-4)
        {
            prev_x = target_x;
        }
        if (abs(current_y - target_y) <= 10e-4)
        {
            prev_y = target_y;
        }
        if (abs(current_rotationZ - target_rotationZ) <= 10e-4)
        {
            prev_rotationZ = target_rotationZ;
        }*/
    }
}

Matrix* DisplayObject::getGlobalMatrix()
{
    if (root != 0)
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
    float kx = 1;
    float ky = 1;
    if (isWHsettedup)
    {
        kx = outer_width / inner_width;
        ky = outer_height / inner_height;
    }
    Matrix a = Matrix::translation(Vector2D(-rx * inner_width, -ry * inner_height));
    Matrix b = Matrix::scaling(Vector2D(current_scaleX * kx, current_scaleY * ky));
    Matrix c = Matrix::rotationZ(current_rotationZ);
    Matrix d = Matrix::translation(Vector2D(rx * inner_width, ry * inner_height));
    Matrix e = Matrix::translation(Vector2D(current_x - rx * inner_width, current_y - ry * inner_height));
    //QMatrix
    a.mul(b);
    a.mul(c);
    a.mul(d);
    a.mul(e);
    *lmatrix = a;
    return lmatrix;
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

    nx = p->M21 * inner_height + p->M31;
    ny = p->M22 * inner_height + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->M11 * inner_width + p->M31;
    ny = p->M12 * inner_width + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    nx = p->M11 * inner_width + p->M21 * inner_height + p->M31;
    ny = p->M12 * inner_width + p->M22 * inner_height + p->M32;

    x1 = std::min(x1, nx);
    y1 = std::min(y1, ny);
    x2 = std::max(x2, nx);
    y2 = std::max(y2, ny);

    return QRectF(x1, y1, x2 - x1, y2 - y1);
}

void DisplayObject::setWidth(float value)
{
    outer_width = value;
    isWHsettedup = true;
}

/*float DisplayObject::getWidth()
{
    Matrix* res = getRenderMatrix();
    return (float)(inner_height * abs(res->M12) + inner_width * abs(res->M11));
}*/

void DisplayObject::setHeight(float value)
{
    outer_height = value;
    isWHsettedup = true;
}

/*float DisplayObject::getHeight()
{
    Matrix* res = getRenderMatrix();
    return (float)(inner_width * abs(res->M12) + inner_height * abs(res->M11));
}*/

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
    rx = c.x;
    ry = c.y;
}

bool DisplayObject::hitTestPoint(float x, float y)
{
    return (render_bounds.top() <= y && y <= render_bounds.bottom() && render_bounds.left() <= x && x <= render_bounds.right());
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
