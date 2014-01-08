#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H
#include "vector2d.h"

struct Point2D
{
    double x, y;

    Point2D();
    Point2D(double x, double y);
    Point2D(Vector2D const & vector);
    Vector2D toVector() const;
    double getDistTo(Point2D const & other) const;
    bool equals(Point2D const & other) const;
    Vector2D getVectorTo(Point2D const & other) const;
    Point2D getPoint(Vector2D const & vector) const;
    Point2D getMiddle(Point2D const& point) const;
};

struct Line2D
{
    double a, b, c;

    Line2D();
    Line2D(double a, double b, double c);
    Line2D(Point2D const & p1, Point2D const & p2);
    Line2D(Point2D const & point, Vector2D const & direction);
    Vector2D getNormal() const;
    bool isParallelTo(Line2D const & line) const;
    Point2D getCrossBy(Line2D const & line) const;
    double getDistTo(Point2D const & point) const;
    bool contains(Point2D const & point) const;
    Point2D getProjection(Point2D const & point) const;
    Vector2D getProjection(Vector2D const & vector) const;
};

struct CrossingResult2D
{
    bool crossing;
    Point2D center;

    CrossingResult2D()
        : crossing(false)
    {
    }

    CrossingResult2D(bool crossing, Point2D const & center)
        : center(center), crossing(crossing)
    {
    }
};

struct AABB
{
    double left, right;
    double top, bottom;

    AABB(double left, double right, double bottom, double top)
    {
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
    }

    bool cross(AABB const & other)
    {
        return (this->left < other.right) && (other.left < this->right)
                && (this->bottom < other.top) && (other.bottom < this->top);
    }
};

struct Segment2D;
struct Rectangle2D;
struct Circle2D;

class Shape2D
{
protected:
    Point2D rotating_point;
    Point2D geometry_center;
    Vector2D r_point_to_center;
    double angle;

public:
    Shape2D(Point2D const & geometry_center, double angle)
        : geometry_center(geometry_center), rotating_point(geometry_center), angle(angle)
    {
    }

    virtual ~Shape2D()
    {
    }

    virtual Point2D getGeometryCenter() const
    {
        return this->geometry_center;
    }

    virtual Point2D getRotatingPoint() const
    {
        return this->rotating_point;
    }

    virtual void setRotatingPoint(Point2D const & rotating_point)
    {
        this->rotating_point = rotating_point;
        r_point_to_center = this->rotating_point.getVectorTo(geometry_center);
    }

    virtual void move(double x, double y)
    {
        rotating_point.x += x;
        rotating_point.y += y;
        geometry_center.x += x;
        geometry_center.y += y;
    }

    virtual double getAngle() const
    {
        return this->angle;
    }

    virtual void rotate(double angle)
    {
        static const double PI = 3.14159265;
        this->angle += angle;
        this->angle -= 2 * PI * (int)(this->angle / (2 * PI));
        r_point_to_center.rotate(angle);
        geometry_center = rotating_point.getPoint(r_point_to_center);
    }

    virtual double getDepth(Point2D const & point) = 0;
    virtual double getWidth() = 0;
    virtual double getHeight() = 0;
    virtual AABB getAABB() = 0;
    virtual bool contains(Point2D const & point) const = 0;
    virtual CrossingResult2D cross(const Shape2D* shape) const = 0;
    virtual CrossingResult2D cross(const Segment2D* segment) const = 0;
    virtual CrossingResult2D cross(const Circle2D* circle) const = 0;
    virtual CrossingResult2D cross(const Rectangle2D* rectangle) const = 0;
};

struct Segment2D : public Shape2D
{
    double length;
    Point2D p1, p2;
    Line2D line;

    Segment2D(Point2D const& p1, Point2D const& p2);
    Segment2D(Point2D const & center, double length, double angle);
    virtual ~Segment2D();
    virtual void rotate(double angle);
    virtual void move(double x, double y);
    virtual bool contains(Point2D const & point) const;
    virtual double getLength();
    virtual double getDepth(const Point2D &point);
    virtual double getWidth();
    virtual double getHeight();
    virtual AABB getAABB();
    virtual CrossingResult2D cross(const Shape2D* shape) const;
    virtual CrossingResult2D cross(const Segment2D* segment) const;
    virtual CrossingResult2D cross(const Circle2D* circle) const;
    virtual CrossingResult2D cross(const Rectangle2D* rectangle) const;
};

struct Circle2D : public Shape2D
{
    double radius;

    Circle2D(Point2D const & center, double radius, double angle);
    virtual ~Circle2D();
    virtual bool contains(Point2D const & point) const;
    virtual double getRadius();
    virtual void setRadius(double radius);
    virtual Segment2D getCrossBy(Line2D const & line) const;
    virtual double getDepth(const Point2D &point);
    virtual double getWidth();
    virtual double getHeight();
    virtual AABB getAABB();
    virtual CrossingResult2D cross(const Shape2D* shape) const;
    virtual CrossingResult2D cross(const Segment2D* segment) const;
    virtual CrossingResult2D cross(const Circle2D* circle) const;
    virtual CrossingResult2D cross(const Rectangle2D* rectangle) const;
};

struct Rectangle2D : public Shape2D
{
    double width, height;
    Point2D a, b, c, d;
    Segment2D * ab, * bc, * cd, * da;

    Rectangle2D(Point2D const & center, double width, double height, double angle);
    Rectangle2D(Point2D const & a, Point2D const & b, Point2D const & c, Point2D const & d);
    virtual ~Rectangle2D();
    virtual bool contains(Point2D const & point) const;
    virtual void rotate(double angle);
    virtual void move(double x, double y);
    virtual double getWidth();
    virtual void setWidth(double width);
    virtual double getHeight();
    virtual void setHeight(double height);
    virtual double getDepth(const Point2D &point);
    virtual AABB getAABB();
    virtual CrossingResult2D cross(const Shape2D* shape) const;
    virtual CrossingResult2D cross(const Segment2D* segment) const;
    virtual CrossingResult2D cross(const Circle2D* circle) const;
    virtual CrossingResult2D cross(const Rectangle2D* rectangle) const;

private:
    void recalculatePoints();
};

#endif // GEOMETRY2D_H
