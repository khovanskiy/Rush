#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QMatrix>
#include <QPainter>
#include <QRectF>

#include "eventdispatcher.h"
#include "eventhandler.h"

#include "vector2d.h"
#include "matrix.h"

class DisplayObject : public EventDispatcher
{
public:
    DisplayObject();
    virtual ~DisplayObject();
    Matrix* getLocalMatrix();
    Matrix* getGlobalMatrix();
    virtual void render(QPainter* render2d, const Matrix& base, bool t, float new_int);

    void setX(float x)
    {
        if (isInt)
        {
            prev_x = target_x;
            target_x = x;
        }
        else
        {
            current_x = x;
        }
    }

    float getX() const
    {
        if (isInt)
        {
            return target_x;
        }
        else
        {
            return current_x;
        }
    }
    void setY(float y)
    {
        if (isInt)
        {
            prev_y = target_y;
            target_y = y;
        }
        else
        {
            current_y = y;
        }
    }
    float getY() const { return current_y; }
    void setInter(bool i) { isInt = i; }
    void setRotationZ(float rotationZ)
    {
        if (isInt)
        {
            prev_rotationZ = target_rotationZ;
            target_rotationZ = rotationZ;
        }
        else
        {
            current_rotationZ = rotationZ;
        }
    }
    float getRotationZ() const
    {
        if (isInt)
        {
            return target_rotationZ;
        }
        else
        {
            return current_rotationZ;
        }
    }
    void setScaleX(float scaleX)
    {
        if (isInt)
        {
            prev_scaleX = target_scaleX;
            target_scaleX = scaleX;
        }
        else
        {
            current_scaleX = scaleX;
        }
    }
    float getScaleX() const
    {
        if (isInt)
        {
            return target_scaleX;
        }
        else
        {
            return current_scaleX;
        }
    }
    void setScaleY(float scaleY)
    {
        if (isInt)
        {
            prev_scaleY = target_scaleY;
            target_scaleY = scaleY;
        }
        else
        {
            current_scaleY = scaleY;
        }
    }
    float getScaleY() const
    {
        if (isInt)
        {
            return target_scaleY;
        }
        else
        {
            return current_scaleY;
        }
    }
    void setVisible(bool visible) { _visible = visible; }
    bool isVisible() const;
    void setWidth(float);
    //float getWidth();
    void setHeight(float);
    //float getHeight();
    void setRatio(bool ratio) { _ratio = ratio; }
    bool isRatio() const { return _ratio; }
    void setRSPointCenter();
    void setRSPoint(const Vector2D&);
    bool hitTestPoint(float x, float y);
    QString h(int, QString);
protected:
    float prev_rotationZ;
    float current_rotationZ;
    float target_rotationZ;
    float speed_rotationZ;

    float current_x;
    float current_y;
    float current_scaleX;
    float current_scaleY;

    float target_x;
    float target_y;
    float target_scaleX;
    float target_scaleY;

    float prev_x;
    float prev_y;
    float prev_scaleX;
    float prev_scaleY;

    float rx;
    float ry;

    float inner_width;
    float inner_height;

    float outer_width;
    float outer_height;

    bool _visible;
    bool _ratio;
    Matrix* gmatrix;
    Matrix* lmatrix;

    bool isWHsettedup;

    QRectF getBounds(Matrix*) const;
    QRectF render_bounds;
private:
    DisplayObject* root;
    bool ready;
    bool isInt;
};

#endif // DISPLAYOBJECT_H
