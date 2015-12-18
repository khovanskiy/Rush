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

class DisplayObject : public TransformableObject, public EventDispatcher {
public:
    DisplayObject();

    virtual ~DisplayObject();

    virtual void render(QPainter *render2d, const Matrix &base, bool t, double new_int);

    void setX(double x) {
        if (isInt) {
            prev_x = target_position.x;
            target_position.x = x;
        }
        else {
            prev_x = position.x = x;
        }
    }

    double getX() const {
        if (isInt) {
            return target_position.x;
        }
        else {
            return position.x;
        }
    }

    void setPosition(const Vector2D &p) {
        setX(p.x);
        setY(p.y);
    }

    const Vector2D &getPosition() const {
        if (isInt) {
            return target_position;
        }
        else {
            return position;
        }
    }

    void setY(double y) {
        if (isInt) {
            prev_y = target_position.y;
            target_position.y = y;
        }
        else {
            prev_y = position.y = y;
        }
    }

    double getY() const {
        if (isInt) {
            return target_position.y;
        }
        else {
            return position.y;
        }
    }

    void setInter(bool i) { isInt = i; }

    void setRotationZ(double rotationZ) {
        if (isInt) {
            prev_rotationZ = target_rotationZ;
            target_rotationZ = rotationZ;
        }
        else {
            this->rotationZ = rotationZ;
        }
    }

    double getRotationZ() const {
        if (isInt) {
            return target_rotationZ;
        }
        else {
            return rotationZ;
        }
    }

    void setScaleX(double scaleX) {
        if (isInt) {
            prev_scaleX = target_scaleX;
            target_scaleX = scaleX;
        }
        else {
            scaling.x = scaleX;
        }
    }

    double getScaleX() const {
        if (isInt) {
            return target_scaleX;
        }
        else {
            return scaling.x;
        }
    }

    void setScaleY(double scaleY) {
        if (isInt) {
            prev_scaleY = target_scaleY;
            target_scaleY = scaleY;
        }
        else {
            scaling.y = scaleY;
        }
    }

    double getScaleY() const {
        if (isInt) {
            return target_scaleY;
        }
        else {
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
    double prev_rotationZ;
    double target_rotationZ;
    double speed_rotationZ;

    Vector2D target_position;
    double target_scaleX;
    double target_scaleY;

    double prev_x;
    double prev_y;
    double prev_scaleX;
    double prev_scaleY;

    bool _visible;
    bool _ratio;

    QRectF *bounds;
private:
    DisplayObject *root;
    bool ready;
    bool isInt;
};

#endif // DISPLAYOBJECT_H
