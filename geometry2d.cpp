#include "geometry2d.h"
#include "math.h"
#include "console.h"

static const double eps = 1e-3;

Point2D::Point2D()
{
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point2D::Point2D(const Vector2D &vector)    
{
    this->x = vector.x;
    this->y = vector.y;
}

Vector2D Point2D::toVector() const
{
    return Vector2D(x, y);
}

double Point2D::getDistTo(const Point2D &other) const
{
    return this->getVectorTo(other).getLength();
}

bool Point2D::equals(const Point2D &other) const
{
    return this->getDistTo(other) < eps;
}

Vector2D Point2D::getVectorTo(const Point2D &other) const
{
    return Vector2D(other.x - this->x, other.y - this->y);
}

Point2D Point2D::getPoint(const Vector2D &vector) const
{
    return Point2D(this->x + vector.x, this->y + vector.y);
}

Point2D Point2D::getMiddle(const Point2D &point) const
{
    return Point2D((this->x + point.x) / 2, (this->y + point.y) / 2);
}

Line2D::Line2D(double a, double b, double c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Line2D::Line2D()
{
    this->a = 1;
    this->b = -1;
    this->c = 0;
}

Line2D::Line2D(const Point2D &p1, const Point2D &p2)
{
    this->a = p2.y - p1.y;
    this->b = p1.x - p2.x;
    this->c = -a * p1.x - b * p1.y;
}

Line2D::Line2D(const Point2D &point, const Vector2D &direction)
{
    this->a = direction.y;
    this->b = -direction.x;
    this->c = -a * point.x - b * point.y;
}

Vector2D Line2D::getNormal() const
{
    return Vector2D(a / sqrt(a * a + b * b), b / sqrt(a * a + b * b));
}

bool Line2D::isParallelTo(const Line2D &other) const
{
    return (abs(this->a * other.b - this->b * other.a) <= eps * abs(this->a * other.b));
}

Point2D Line2D::getCrossBy(const Line2D &other) const
{
    return Point2D((this->c * other.b - this->b * other.c) / (this->b * other.a - this->a * other.b),
                   (this->c * other.a - this->a * other.c) / (this->a * other.b - this->b * other.a));
}

double Line2D::getDistTo(const Point2D &point) const
{
    return abs(point.x * a + point.y * b + c) / sqrt(a * a + b * b);
}

bool Line2D::contains(const Point2D &point) const
{
    return (getDistTo(point) <= eps);
}

Point2D Line2D::getProjection(const Point2D &point) const
{
    double s = sqrt(a * a + b * b);
    double len = (point.x * a + point.y * b + c) / s;
    return Point2D(point.x - len * a / s, point.y - len * b / s);
}

Vector2D Line2D::getProjection(const Vector2D &vector) const
{
    Vector2D n = getNormal();
    Vector2D v = vector;
    double k = v.scalar(n);
    n.mul(k);
    v.sub(n);
    return v;
}

Segment2D::Segment2D(const Point2D &p1, const Point2D &p2)
    : Shape2D(Point2D((p1.x + p2.x) / 2, (p1.y + p2.y) / 2), -asin(1) + atan2(p2.y - p1.y, p2.x - p1.x)),
      p1(p1), p2(p2), line(p1, p2), length(p1.getDistTo(p2))
{
    //Console::print("Creating segment...");
    //Console::print("Segment has been created");
}

Segment2D::Segment2D(const Point2D &center, double length, double angle)
    : Shape2D(center, angle), length(length)
{
    //Console::print("Creating segment...");
    Vector2D v(0, length / 2);
    v.rotate(angle);
    this->p2 = this->geometry_center.getPoint(v);
    v.mul(-1);
    this->p1 = this->geometry_center.getPoint(v);
    this->line = Line2D(p1, p2);
    //Console::print("Segment has been created");
}

Segment2D::~Segment2D()
{
}

double Segment2D::getLength()
{
    return this->length;
}

void Segment2D::rotate(double angle)
{
    this->Shape2D::rotate(angle);
    Vector2D v(length / 2, 0);
    v.rotate(this->getAngle());
    this->p2 = this->geometry_center.getPoint(v);
    v.mul(-1);
    this->p1 = this->geometry_center.getPoint(v);
    this->line = Line2D(p1, p2);
}

void Segment2D::move(double x, double y)
{
    this->Shape2D::move(x, y);
    p1 = p1.getPoint(Vector2D(x, y));
    p2 = p2.getPoint(Vector2D(x, y));
}

bool Segment2D::contains(const Point2D &point) const
{
    return line.contains(point) &&
            ((p1.x - point.x) * (p2.x - point.x) <= eps)
            && ((p1.y - point.y) * (p2.y - point.y) <= eps);
}

CrossingResult2D Segment2D::cross(const Shape2D *other) const
{
    return other->cross(this);
}

CrossingResult2D Segment2D::cross(const Segment2D *segment) const
{
    /*Console::print("Segment crosses segment:");
    Console::print("Segment 1:");
    Console::print(this->p1.toVector());
    Console::print(this->p2.toVector());
    Console::print("Segment 2:");
    Console::print(segment->p1.toVector());
    Console::print(segment->p2.toVector());/**/
    if (this->line.isParallelTo(segment->line))
    {
        //Console::print("Segments are parallel.");
        Point2D points[4];
        int amount = 0;
        if (this->contains(segment->p1)) points[amount++] = segment->p1;
        if (this->contains(segment->p2)) points[amount++] = segment->p2;
        if (segment->contains(this->p1)) points[amount++] = this->p1;
        if (segment->contains(this->p2)) points[amount++] = this->p2;
        if (amount == 0)
        {
            return CrossingResult2D(false, Point2D(0, 0));
        }
        else
        {
            Point2D first = points[0];
            Point2D second = first;
            for (int i = 1; i < amount; i++)
            {
                if (!points[i].equals(first)) second = points[i];
            }
            return CrossingResult2D(true, first.getMiddle(second));
        }        
    }
    else
    {
        //Console::print("Segments aren\'t parallel");
        Point2D p = this->line.getCrossBy(segment->line);
        //Console::print("Lines crosses at:");
        //Console::print(p.toVector());
        if (this->contains(p) && segment->contains(p))
        {
            return CrossingResult2D(true, p);
        }
        else
        {
            return CrossingResult2D(false, p);
        }
    }
}

CrossingResult2D Segment2D::cross(const Circle2D *circle) const
{
    return circle->cross(this);
}

CrossingResult2D Segment2D::cross(const Rectangle2D *rectangle) const
{
    return rectangle->cross(this);
}

double Segment2D::getDepth(const Point2D &point)
{
    double l1 = this->getRotatingPoint().getDistTo(p1);
    double l2 = this->getRotatingPoint().getDistTo(p2);
    double max = (l1 > l2 ? l1 : l2);
    return max - this->getRotatingPoint().getDistTo(point);
}

double Segment2D::getWidth()
{
    return 0;
}

double Segment2D::getHeight()
{
    return getLength();
}

AABB Segment2D::getAABB()
{
    double w = abs(this->p1.x - this->geometry_center.x);
    double h = abs(this->p1.y - this->geometry_center.y);
    return AABB(this->geometry_center.x - w, this->geometry_center.x + w,
                this->geometry_center.y - h, this->geometry_center.y + h);
}

Point2D Segment2D::segmentCrossBorder(const Segment2D *segment) const
{
    return this->line.getCrossBy(segment->line);
}

Circle2D::Circle2D(const Point2D &center, double radius, double angle)
    : Shape2D(center, angle)
{
    this->radius = radius;
}

Circle2D::~Circle2D()
{
}

bool Circle2D::contains(const Point2D &point) const
{
    return this->geometry_center.getDistTo(point) < this->radius + eps;
}

double Circle2D::getRadius()
{
    return this->radius;
}

void Circle2D::setRadius(double radius)
{
    this->radius = radius;
}

Segment2D Circle2D::getCrossBy(const Line2D &line) const
{
    Point2D projection = line.getProjection(geometry_center);
    double dist = this->geometry_center.getDistTo(projection);
    double len = sqrt(radius * radius - dist * dist);
    double s = sqrt(line.a * line.a + line.b * line.b);
    Point2D p1 = Point2D(projection.x - len * line.b / s, projection.y + len * line.a / s);
    Point2D p2 = Point2D(projection.x + len * line.b / s, projection.y - len * line.a / s);
    return Segment2D(p1, p2);
}

double Circle2D::getDepth(const Point2D &point)
{
    return this->radius - this->getGeometryCenter().getDistTo(point);
}

double Circle2D::getWidth()
{
    return 2 * radius;
}

double Circle2D::getHeight()
{
    return 2 * radius;
}

AABB Circle2D::getAABB()
{
    return AABB(this->geometry_center.x - this->radius, this->geometry_center.x + this->radius,
                this->geometry_center.y - this->radius, this->geometry_center.y + this->radius);
}

CrossingResult2D Circle2D::cross(const Shape2D* shape) const
{
    return shape->cross(this);
}

CrossingResult2D Circle2D::cross(const Segment2D *segment) const
{
    if (segment->line.getDistTo(this->geometry_center) > this->radius)
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }
    else
    {
        return this->getCrossBy(segment->line).cross(segment);
    }
}

CrossingResult2D Circle2D::cross(const Circle2D *circle) const
{
    double l = this->geometry_center.getDistTo(circle->geometry_center);
    if (l > this->radius + circle->radius)
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }
    else
    {
        double d = (l * l + this->radius * this->radius - circle->radius * circle->radius) / (2 * l);
        Point2D point = Point2D(
                    this->geometry_center.x + d * (circle->geometry_center.x - this->geometry_center.x) / l,
                    this->geometry_center.y + d * (circle->geometry_center.y - this->geometry_center.y) / l);
        return CrossingResult2D(true, point);
    }
}

CrossingResult2D Circle2D::cross(const Rectangle2D *rectangle) const
{
    return rectangle->cross(this);
}

Point2D Circle2D::segmentCrossBorder(const Segment2D *segment) const
{
    if (segment->cross(this).crossing)
    {
        Segment2D seg = getCrossBy(segment->line);
        if (seg.p1.getVectorTo(seg.p2).scalar(segment->p1.getVectorTo(segment->p2)) > 0)
        {
            return seg.p1;
        }
        else
        {
            return seg.p2;
        }
    }
    else
    {
        return segment->line.getProjection(this->getGeometryCenter());
    }
}

void Rectangle2D::recalculatePoints()
{
    Vector2D va(-width / 2, -height / 2);
    Vector2D vb(-width / 2, height / 2);
    Vector2D vc(width / 2, height / 2);
    Vector2D vd(width / 2, -height / 2);
    va.rotate(angle);
    vb.rotate(angle);
    vc.rotate(angle);
    vd.rotate(angle);
    a = Point2D(geometry_center.x + va.x, geometry_center.y + va.y);
    b = Point2D(geometry_center.x + vb.x, geometry_center.y + vb.y);
    c = Point2D(geometry_center.x + vc.x, geometry_center.y + vc.y);
    d = Point2D(geometry_center.x + vd.x, geometry_center.y + vd.y);
    if (ab != 0)
    {
        delete ab;
        delete bc;
        delete cd;
        delete da;
    }
    ab = new Segment2D(a, b);
    bc = new Segment2D(b, c);
    cd = new Segment2D(c, d);
    da = new Segment2D(d, a);    
}

Rectangle2D::Rectangle2D(const Point2D &center, double width, double height, double angle)
    : Shape2D(center, angle)
{
    //Console::print("Creating rectangle...");
    this->width = width;
    this->height = height;
    ab = 0;
    bc = 0;
    cd = 0;
    da = 0;
    recalculatePoints();
    //Console::print("Rectangle has been created.");
}

Rectangle2D::Rectangle2D(const Point2D &a, const Point2D &b, const Point2D &c, const Point2D &d)
    : Shape2D(Point2D((a.x + c.x) / 2, (a.y + c.y) / 2), atan2(b.y - a.y, b.x - a.x)),
      a(a), b(b), c(c), d(d)
{
    //Console::print("Creating rectangle...");
    this->width = a.getDistTo(d);
    this->height = a.getDistTo(b);
    recalculatePoints();
    //Console::print("Rectangle has been created.");
}

Rectangle2D::~Rectangle2D()
{
    delete ab;
    delete bc;
    delete cd;
    delete da;
}

bool Rectangle2D::contains(const Point2D &point) const
{
    Vector2D v = point.toVector();
    v.sub(this->getGeometryCenter().toVector());
    v.rotate(-this->angle);
    return (v.x > -width / 2 - 10 * eps) && (v.x < width / 2 + 10 * eps)
            && (v.y > -height / 2 - 10 * eps) && (v.y < height / 2 + 10 * eps);
}

void Rectangle2D::rotate(double angle)
{
    this->Shape2D::rotate(angle);
    recalculatePoints();
}

void Rectangle2D::move(double x, double y)
{
    this->Shape2D::move(x, y);
    recalculatePoints();
}

double Rectangle2D::getHeight()
{
    return this->height;
}

void Rectangle2D::setHeight(double height)
{
    this->height = height;
    recalculatePoints();
}

double Rectangle2D::getWidth()
{
    return this->width;
}

void Rectangle2D::setWidth(double width)
{
    this->width = width;
    recalculatePoints();
}

double Rectangle2D::getDepth(const Point2D &point)
{
    double p1 = point.getDistTo(ab->line.getProjection(point));
    double p2 = point.getDistTo(bc->line.getProjection(point));
    double p3 = point.getDistTo(cd->line.getProjection(point));
    double p4 = point.getDistTo(da->line.getProjection(point));
    if (p3 < p1) p1 = p3;
    if (p4 < p2) p2 = p4;
    if (width / 2 - p1 > height / 2 - p2)
    {
        return width / 2 - p1;
    }
    else
    {
        return height / 2 - p2;
    }
}

AABB Rectangle2D::getAABB()
{
    double w = abs(this->a.x - this->geometry_center.x);
    double w1 = abs(this->b.x - this->geometry_center.x);
    if (w1 > w) w = w1;
    double h = abs(this->a.y - this->geometry_center.y);
    double h1 = abs(this->b.y - this->geometry_center.y);
    if (h1 > h) h = h1;
    return AABB(this->geometry_center.x - w, this->geometry_center.x + w,
                this->geometry_center.y - h, this->geometry_center.y + h);
}

CrossingResult2D Rectangle2D::cross(const Shape2D *shape) const
{
    return shape->cross(this);
}

CrossingResult2D Rectangle2D::cross(const Segment2D *segment) const
{
    /*Console::print("Rectangle crosses segment.");
    Console::print("Rectangle:");
    Console::print(this->ab->p1.toVector());
    Console::print(this->ab->p2.toVector());
    Console::print(this->cd->p1.toVector());
    Console::print(this->cd->p2.toVector());
    Console::print("Segment:");
    Console::print(segment->p1.toVector());
    Console::print(segment->p2.toVector());
    Console::print("Points inside:");/**/
    int last = 0, amount = 0;
    if (this->contains(segment->p1))
    {
        last = 1;
        amount++;
        //Console::print(segment->p1.toVector());
    }
    if (this->contains(segment->p2))
    {
        last = 2;
        amount++;
        //Console::print(segment->p2.toVector());
    }
    if (amount == 0)
    {
        Point2D points[4];
        int head = 0;
        CrossingResult2D result = ab->cross(segment);
        if (result.crossing) points[head++] = result.center;
        result = bc->cross(segment);
        if (result.crossing) points[head++] = result.center;
        result = cd->cross(segment);
        if (result.crossing) points[head++] = result.center;
        result = da->cross(segment);
        if (result.crossing) points[head++] = result.center;
        //Console::print("Total sides crossings:");
        //Console::print(head);
        switch (head)
        {
        case 0:
            return CrossingResult2D(false, Point2D(0, 0));
        case 1:
            return CrossingResult2D(true, points[0]);
        case 2:
            return CrossingResult2D(true, points[0].getMiddle(points[1]));
        case 3:
            return CrossingResult2D(true,
                    (points[0].equals(points[1])) ?
                        points[0].getMiddle(points[2])
                    : points[0].getMiddle(points[1]));
        default:
            return CrossingResult2D(true, this->geometry_center);
        }
    }
    else if (amount == 1)
    {
        Point2D point_inside = ((last == 1) ? segment->p1 : segment->p2);
        Point2D point_on_edge;
        CrossingResult2D result = ab->cross(segment);
        if (result.crossing) point_on_edge = result.center;
        result = bc->cross(segment);
        if (result.crossing) point_on_edge = result.center;
        result = cd->cross(segment);
        if (result.crossing) point_on_edge = result.center;
        result = da->cross(segment);
        if (result.crossing) point_on_edge = result.center;
        //Console::print("Total sides crossings:");
        //Console::print(head);
        return CrossingResult2D(true, point_inside.getMiddle(point_on_edge));
    }
    else
    {
        return CrossingResult2D(true, segment->getGeometryCenter());
    }
}

CrossingResult2D Rectangle2D::cross(const Circle2D *circle) const
{
    CrossingResult2D results[4];
    results[0] = circle->cross(ab);
    results[1] = circle->cross(bc);
    results[2] = circle->cross(cd);
    results[3] = circle->cross(da);
    int amount = 0;
    double x = 0, y = 0;
    for (int i = 0; i < 4; i++) if (results[i].crossing)
    {
        amount++;
        x += results[i].center.x;
        y += results[i].center.y;
    }
    if (amount == 0)
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }    
    else
    {
        x /= amount;
        y /= amount;
        return CrossingResult2D(true, Point2D(x, y));
    }
}

CrossingResult2D Rectangle2D::cross(const Rectangle2D *rectangle) const
{
    CrossingResult2D results[8];
    results[0] = rectangle->cross(ab);
    results[1] = rectangle->cross(bc);
    results[2] = rectangle->cross(cd);
    results[3] = rectangle->cross(da);
    results[4] = this->cross(rectangle->ab);
    results[5] = this->cross(rectangle->bc);
    results[6] = this->cross(rectangle->cd);
    results[7] = this->cross(rectangle->da);
    int amount = 0;
    double x = 0, y = 0;
    for (int i = 0; i < 8; i++) if (results[i].crossing)
    {
        amount++;
        x += results[i].center.x;
        y += results[i].center.y;
    }
    if (amount == 0)
    {
        return CrossingResult2D(false, Point2D(0, 0));
    }    
    else
    {
        x /= amount;
        y /= amount;
        return CrossingResult2D(true, Point2D(x, y));
    }
}

Point2D Rectangle2D::segmentCrossBorder(const Segment2D *segment) const
{
    Point2D points[8];
    points[0] = ab->line.getCrossBy(segment->line);
    points[1] = bc->line.getCrossBy(segment->line);
    points[2] = cd->line.getCrossBy(segment->line);
    points[3] = da->line.getCrossBy(segment->line);
    Vector2D dir = segment->p1.getVectorTo(segment->p2);
    dir.mul(-10);
    Point2D p = segment->p1.getPoint(dir);
    bool found = false;
    Point2D closest;
    for (int i = 0; i < 4; i++)
    {
        if (this->contains(points[i]))
        {
            if (!found || points[i].getDistTo(p) < closest.getDistTo(p))
            {
                closest = points[i];
                found = true;
            }
        }
    }
    if (found)
    {
        return closest;
    }
    else
    {
        return segment->p1;
    }

}
