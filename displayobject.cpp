#include "displayobject.h"
#include "math.h"
#include "console.h"
#include "mouse.h"
#include "mouseevent.h"
#include <numeric>
#include <cmath>

DisplayObject::DisplayObject()
{
    _visible = true;

    prev_x = 0;
    prev_y = 0;

    speed_rotationZ = prev_rotationZ = target_rotationZ = 0;

    prev_scaleX = target_scaleX = 1;
    prev_scaleY = target_scaleY = 1;

    _ratio = false;
    root = 0;
    ready = false;

    isInt = false;

    bounds = new QRectF();
}

DisplayObject::~DisplayObject()
{
    delete bounds;
}

void DisplayObject::render(QPainter *, const Matrix &base, bool new_tick, float interpolation)
{
    if (isInt)
    {
        if (new_tick)
        {
            prev_x = target_position.x;
            prev_y = target_position.y;
            prev_scaleX = target_scaleX;
            prev_scaleY = target_scaleY;
            prev_rotationZ = target_rotationZ;
        }

        rotationZ = prev_rotationZ + (target_rotationZ - prev_rotationZ) * interpolation;

        position.x = prev_x + (target_position.x - prev_x) * interpolation;
        position.y = prev_y + (target_position.y - prev_y) * interpolation;
        scaling.x = prev_scaleX + (target_scaleX - prev_scaleX) * interpolation;
        scaling.y = prev_scaleY + (target_scaleY - prev_scaleY) * interpolation;

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

void DisplayObject::setWidth(float value)
{
    outer_size.x = value;
    isWHsettedup = true;
}

/*float DisplayObject::getWidth()
{
    Matrix* res = getRenderMatrix();
    return (float)(inner_height * abs(res->M12) + inner_width * abs(res->M11));
}*/

void DisplayObject::setHeight(float value)
{
    outer_size.y = value;
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

bool DisplayObject::hitTestPoint(float x, float y)
{
    return (bounds->top() <= y && y <= bounds->bottom() && bounds->left() <= x && x <= bounds->right());
}
