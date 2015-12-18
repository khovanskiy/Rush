#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include <QRectF>
#include "matrix.h"
#include "vector2d.h"

class TransformableObject
{
public:
    TransformableObject();
    virtual ~TransformableObject();
    QRectF getBounds(const Matrix&);
    virtual Matrix& getTransform();

    void setSize(const Vector2D& size);
    void setScaling(const Vector2D& scaling);
    const Vector2D& getScaling() const;
    const Vector2D& getSize() const;
    virtual void setPosition(const Vector2D& p);
    virtual const Vector2D& getPosition() const;
    void setRSPoint(const Vector2D& m);
    void setRSPointCenter();
protected:
    Vector2D outer_size;
    Vector2D inner_size;
    bool isWHsettedup;
    Vector2D scaling;
    Vector2D position;
    Vector2D rs_point;
    double rotationZ;
    Matrix matrix;
    QRectF bounds;
};

#endif // TRANSFORMABLEOBJECT_H
