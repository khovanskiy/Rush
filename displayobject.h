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
    Matrix* getRenderMatrix();
    Matrix* getLocalMatrix();
    Matrix* getGlobalMatrix();
    virtual void render(QPainter*, const Matrix& base);
    void setX(float x) { _x = x; }
    float getX() const { return _x;}
    void setY(float y) { _y = y; }
    float getY() const { return _y; }
    void setRotationZ(float rotationZ) { _rotationZ = rotationZ; }
    float getRotationZ() const { return _rotationZ; }
    void setScaleX(float scaleX) { _scaleX = scaleX; }
    float getScaleX() const { return _scaleX; }
    void setScaleY(float scaleY) { _scaleY = scaleY; }
    float getScaleY() const { return _scaleY; }
    void setVisible(bool visible) { _visible = visible; }
    bool isVisible() const;
    void setWidth(float);
    float getWidth();
    void setHeight(float);
    float getHeight();
    void setRatio(bool ratio) { _ratio = ratio; }
    bool isRatio() const { return _ratio; }
    void setRSPointCenter();
    void setRSPoint(const Vector2D&);
    virtual QRectF getRenderBounds();
    bool hitTestPoint(float x, float y);
    QString h(int, QString);
protected:
    float _x;
    float _y;
    float _rotationZ;
    float _scaleX;
    float _scaleY;
    float rx;
    float ry;
    float _width;
    float _height;
    bool _visible;
    bool _ratio;
    Matrix* gmatrix;
    Matrix* lmatrix;
private:
    DisplayObject* root;
    //FunctionProxy* do_proxy;
    QRectF getBounds(Matrix*) const;
};

#endif // DISPLAYOBJECT_H
