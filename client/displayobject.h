#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QMatrix>
#include <QPainter>
#include <QRectF>

#include "../common/eventdispatcher.h"
#include "../common/eventhandler.h"
#include "../common/transformableobject.h"

#include "../common/vector2d.h"
#include "../common/matrix.h"

class DisplayObject : public TransformableObject, public EventDispatcher
{
public:
    DisplayObject();
    virtual ~DisplayObject();
    virtual void render(QPainter* render2d, const Matrix& base, bool t, float new_int);

    void setX(float x)
    {
        if (isInt)
        {
            prev_x = target_position.x;
            target_position.x = x;
        }
        else
        {
            prev_x = position.x = x;
        }
    }

    float getX() const
    {
        if (isInt)
        {
            return target_position.x;
        }
        else
        {
            return position.x;
        }
    }
    void setPosition(const Vector2D& p)
    {
        setX(p.x);
        setY(p.y);
    }

    const Vector2D& getPosition() const
    {
        if (isInt)
        {
            return target_position;
        }
        else
        {
            return position;
        }
    }

    void setY(float y)
    {
        if (isInt)
        {
            prev_y = target_position.y;
            target_position.y = y;
        }
        else
        {
            prev_y = position.y = y;
        }
    }
    float getY() const
    {
        if (isInt)
        {
            return target_position.y;
        }
        else
        {
            return position.y;
        }
    }
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
            this->rotationZ = rotationZ;
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
            return rotationZ;
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
            scaling.x = scaleX;
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
            return scaling.x;
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
            scaling.y = scaleY;
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
            return scaling.y;
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
    bool hitTestPoint(float x, float y);
protected:
    float prev_rotationZ;
    float target_rotationZ;
    float speed_rotationZ;

    Vector2D target_position;
    float target_scaleX;
    float target_scaleY;

    float prev_x;
    float prev_y;
    float prev_scaleX;
    float prev_scaleY;

    bool _visible;
    bool _ratio;

    QRectF* bounds;
private:
    DisplayObject* root;
    bool ready;
    bool isInt;
};

#endif // DISPLAYOBJECT_H
