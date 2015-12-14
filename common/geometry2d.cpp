#include <cmath>
#include "geometry2d.h"
#include "math.h"
#include "console.h"
#include <algorithm>
#include <vector>

static const double eps = 1e-9;


double cross(const Point2D &O, const Point2D &A, const Point2D &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
std::vector<Point2D> convex_hull(std::vector<Point2D> P)
{
    int n = P.size(), k = 0;
    std::vector<Point2D> H(2*n);

    // Sort points lexicographically
    std::sort(P.begin(), P.end());

    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    // Build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    H.resize(k);
    return H;
}

Point2D convexMassCenter(std::vector<Point2D> P)
{
    int n = P.size();
    if (n >= 4)
    {
        double x = 0, y = 0, weight = 0;
        Point2D p0 = P[0];
        for (int i = 1; i < n - 2; i++) {
            double px = (P[i].x + P[i + 1].x + p0.x) / 3;
            double py = (P[i].y + P[i + 1].y + p0.y) / 3;
            double pweight = cross(p0, P[i], P[i + 1]);
            x += px * pweight;
            y += py * pweight;
            weight += pweight;
        }
        return Point2D(x / weight, y / weight);
    }
    else
    {
        double x = 0, y = 0;
        for (int i = 0; i < n - 1; i++) {
            x += P[i].x;
            y += P[i].y;
        }
        int amount = P.size() - 1;
        return Point2D(x / amount, y / amount);
    }

}


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
    return (std::abs(this->a * other.b - this->b * other.a) <= eps * std::abs(this->a * other.b));
}

Point2D Line2D::getCrossBy(const Line2D &other) const
{
    return Point2D((this->c * other.b - this->b * other.c) / (this->b * other.a - this->a * other.b),
                   (this->c * other.a - this->a * other.c) / (this->a * other.b - this->b * other.a));
}

double Line2D::getDistTo(const Point2D &point) const
{
    return std::abs(point.x * a + point.y * b + c) / sqrt(a * a + b * b);
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

Segment2D::Segment2D()
    : Shape2D(Point2D(0, 0.5), 0), p1(Point2D(0, 0)), p2(Point2D(0, 1)), line(p1, p2)
{
}

Segment2D::Segment2D(const Point2D &p1, const Point2D &p2)
    : Shape2D(Point2D((p1.x + p2.x) / 2, (p1.y + p2.y) / 2), -asin(1) + atan2(p2.y - p1.y, p2.x - p1.x)),
      p1(p1), p2(p2), line(p1, p2)
{
}

Segment2D::Segment2D(const Point2D &center, double length, double angle)
    : Shape2D(center, angle)
{
    Vector2D v(0, length / 2);
    v.rotate(angle);
    this->p2 = this->geometry_center.getPoint(v);
    v.mul(-1);
    this->p1 = this->geometry_center.getPoint(v);
    this->line = Line2D(p1, p2);
}

Segment2D::~Segment2D()
{
}

void Segment2D::rotate(double angle)
{
    this->Shape2D::rotate(angle);
    Vector2D v(0, p1.getDistTo(p2) / 2);
    v.rotate(this->angle);
    this->p2 = this->geometry_center.getPoint(v);
    v.mul(-1);
    this->p1 = this->geometry_center.getPoint(v);
    this->line = Line2D(p1, p2);
}

void Segment2D::move(double x, double y)
{
    this->Shape2D::move(x, y);
    p1.x += x;
    p1.y += y;
    p2.x += x;
    p2.y += y;
    this->line = Line2D(p1, p2);
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
    if (this->line.isParallelTo(segment->line))
    {
        Point2D points[4];
        int amount = 0;
        if (this->contains(segment->p1)) points[amount++] = segment->p1;
        if (this->contains(segment->p2)) points[amount++] = segment->p2;
        if (segment->contains(this->p1)) points[amount++] = this->p1;
        if (segment->contains(this->p2)) points[amount++] = this->p2;
        if (amount == 0)
        {
            return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
        }
        else
        {
            Point2D first = points[0];
            Point2D second = first;
            for (int i = 1; i < amount; i++)
            {
                if (!points[i].equals(first)) second = points[i];
            }
            Vector2D normal = Line2D(this->p1, this->p1.getVectorTo(this->p2)).getNormal();
            return CrossingResult2D(true, first.getMiddle(second), normal);
        }        
    }
    else
    {
        Point2D p = this->line.getCrossBy(segment->line);
        if (this->contains(p) && segment->contains(p))
        {
            return CrossingResult2D(true, p, Vector2D(0, 0));
        }
        else
        {
            return CrossingResult2D(false, p, Vector2D(0, 0));
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

double Segment2D::getDepth(const Point2D &point) const
{
    double l1 = this->getRotatingPoint().getDistTo(p1);
    double l2 = this->getRotatingPoint().getDistTo(p2);
    double max = (l1 > l2 ? l1 : l2);
    return max - this->getRotatingPoint().getDistTo(point);
}

double Segment2D::getWidth() const
{
    return 0;
}

double Segment2D::getHeight() const
{
    return p1.getDistTo(p2);
}

AABB Segment2D::getAABB() const
{
    double w = std::abs(this->p1.x - this->geometry_center.x);
    double h = std::abs(this->p1.y - this->geometry_center.y);
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

double Circle2D::getInertiaMoment(double mass)
{
    return mass * radius * radius / 2;
}

bool Circle2D::contains(const Point2D &point) const
{
    return this->geometry_center.getDistTo(point) < this->radius + eps;
}

double Circle2D::getRadius() const
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

double Circle2D::getDepth(const Point2D &point) const
{
    return this->radius - this->getGeometryCenter().getDistTo(point);
}

double Circle2D::getWidth() const
{
    return 2 * radius;
}

double Circle2D::getHeight() const
{
    return 2 * radius;
}

AABB Circle2D::getAABB() const
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
        return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
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
        return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
    }
    else
    {
        double d = (l * l + this->radius * this->radius - circle->radius * circle->radius) / (2 * l);
        Point2D point = Point2D(
                    this->geometry_center.x + d * (circle->geometry_center.x - this->geometry_center.x) / l,
                    this->geometry_center.y + d * (circle->geometry_center.y - this->geometry_center.y) / l);
        return CrossingResult2D(true, point, this->geometry_center.getVectorTo(circle->getGeometryCenter()));
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

std::pair<bool, Segment2D> segCross(const Circle2D * circle, Segment2D * segment)
{
    if (segment->line.getDistTo(circle->getGeometryCenter()) > circle->getRadius())
    {
        return std::make_pair(false, (*segment));
    }
    else
    {
        Segment2D lineCrossed = circle->getCrossBy(segment->line);
        Point2D points[4];
        int amount = 0;
        if (lineCrossed.contains(segment->p1)) points[amount++] = segment->p1;
        if (lineCrossed.contains(segment->p2)) points[amount++] = segment->p2;
        if (segment->contains(lineCrossed.p1)) points[amount++] = lineCrossed.p1;
        if (segment->contains(lineCrossed.p2)) points[amount++] = lineCrossed.p2;
        if (amount > 0)
        {
            Point2D first = points[0];
            Point2D second = first;
            for (int i = 1; i < amount; i++)
            {
                if (!points[i].equals(first)) second = points[i];
            }
            return std::make_pair(true, Segment2D(first, second));

        }
        else
        {
            return std::make_pair(false, (*segment));
        }
    }
}

double Rectangle2D::getInertiaMoment(double mass)
{
    return mass * (width * width + height * height) / 12;
}

void Rectangle2D::calculatePoints()
{
    Vector2D va(-width / 2, -height / 2);
    Vector2D vb(-width / 2, height / 2);
    Vector2D vc(width / 2, height / 2);
    Vector2D vd(width / 2, -height / 2);
    va.rotate(angle);
    vb.rotate(angle);
    vc.rotate(angle);
    vd.rotate(angle);
    Point2D a = geometry_center.getPoint(va);
    Point2D b = geometry_center.getPoint(vb);
    Point2D c = geometry_center.getPoint(vc);
    Point2D d = geometry_center.getPoint(vd);
    ab = new Segment2D(a, b);
    ab->setRotatingPoint(rotating_point);
    bc = new Segment2D(b, c);
    bc->setRotatingPoint(rotating_point);
    cd = new Segment2D(c, d);
    cd->setRotatingPoint(rotating_point);
    da = new Segment2D(d, a);
    da->setRotatingPoint(rotating_point);
}

Rectangle2D::Rectangle2D(const Point2D &center, double width, double height)
    : Shape2D(center, 0)
{
    this->width = width;
    this->height = height;
    calculatePoints();
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
    v.sub(geometry_center.toVector());
    v.rotate(-this->angle);
    return (std::abs(v.x) < width / 2 + eps) && (std::abs(v.y) < height / 2 + eps);
}

void Rectangle2D::setRotatingPoint(const Point2D &rotating_point)
{
    Shape2D::setRotatingPoint(rotating_point);
    ab->setRotatingPoint(rotating_point);
    bc->setRotatingPoint(rotating_point);
    cd->setRotatingPoint(rotating_point);
    da->setRotatingPoint(rotating_point);
}

void Rectangle2D::rotate(double angle)
{
    this->Shape2D::rotate(angle);
    ab->rotate(angle);
    bc->rotate(angle);
    cd->rotate(angle);
    da->rotate(angle);
}

void Rectangle2D::move(double x, double y)
{
    this->Shape2D::move(x, y);
    ab->move(x, y);
    bc->move(x, y);
    cd->move(x, y);
    da->move(x, y);
}

double Rectangle2D::getHeight() const
{
    return this->height;
}

void Rectangle2D::setHeight(double height)
{
    this->height = height;
    calculatePoints();
}

double Rectangle2D::getWidth() const
{
    return this->width;
}

void Rectangle2D::setWidth(double width)
{
    this->width = width;
    calculatePoints();
}

double Rectangle2D::getDepth(const Point2D &point) const
{
    double min = ab->line.getDistTo(point);
    double cur = bc->line.getDistTo(point);
    if (cur < min) min = cur;
    cur = cd->line.getDistTo(point);
    if (cur < min) min = cur;
    cur = da->line.getDistTo(point);
    if (cur < min) min = cur;
    return min;
}

AABB Rectangle2D::getAABB() const
{
    double w = std::abs(this->ab->p1.x - this->geometry_center.x);
    double w1 = std::abs(this->ab->p2.x - this->geometry_center.x);
    if (w1 > w) w = w1;
    double h = std::abs(this->ab->p1.y - this->geometry_center.y);
    double h1 = std::abs(this->ab->p2.y - this->geometry_center.y);
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
    int last = 0, amount = 0;
    if (this->contains(segment->p1))
    {
        last = 1;
        amount++;
    }
    if (this->contains(segment->p2))
    {
        last = 2;
        amount++;
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
        switch (head)
        {
        case 0:
            return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
        case 1:
            return CrossingResult2D(true, points[0], Vector2D(0, 0));
        case 2:
            return CrossingResult2D(true, points[0].getMiddle(points[1]), Vector2D(0, 0));
        case 3:
            return CrossingResult2D(true,
                    (points[0].equals(points[1])) ?
                        points[0].getMiddle(points[2])
                    : points[0].getMiddle(points[1]), Vector2D(0, 0));
        default:
            return CrossingResult2D(true, this->geometry_center, Vector2D(0, 0));
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
        return CrossingResult2D(true, point_inside.getMiddle(point_on_edge), Vector2D(0, 0));
    }
    else
    {
        return CrossingResult2D(true, segment->getGeometryCenter(), Vector2D(0, 0));
    }
}

CrossingResult2D Rectangle2D::cross(const Circle2D *circle) const
{
    std::vector<Point2D> existing = std::vector<Point2D>();
    std::pair<bool, Segment2D> segmentPairs[4];
    segmentPairs[0] = segCross(circle, this->ab);
    segmentPairs[1] = segCross(circle, bc);
    segmentPairs[2] = segCross(circle, cd);
    segmentPairs[3] = segCross(circle, da);
    for (int i = 0; i < 4; i++) if (segmentPairs[i].first)
    {
        existing.push_back(segmentPairs[i].second.p1);
        existing.push_back(segmentPairs[i].second.p2);
    }
    if (existing.size() == 0)
    {
        if (this->contains(circle->getGeometryCenter())) {
            return CrossingResult2D(true, circle->getGeometryCenter(),
                                    this->getGeometryCenter().getVectorTo(circle->getGeometryCenter()));
        } else {
            return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
        }
    }    
    else
    {
        Point2D collisionCenter = convexMassCenter(convex_hull(existing));
        Vector2D direction = geometry_center.getVectorTo(collisionCenter);
        double angle = atan2(direction.y, direction.x) - this->angle;
        if (angle < -M_PI) angle += 2 * M_PI;
        if (angle > M_PI) angle -= 2 * M_PI;
        double diag = atan2(height, width);
        Vector2D normal = Vector2D(0, 0);
        if (std::abs(angle - diag) < M_PI / 36)
        {
            normal = geometry_center.getVectorTo(cd->p1);
        }
        else if (std::abs(angle + diag) < M_PI / 36)
        {
            normal = geometry_center.getVectorTo(da->p1);
        }
        else if (std::abs(angle - (M_PI - diag)) < M_PI / 36)
        {
            normal = geometry_center.getVectorTo(bc->p1);
        }
        else if (std::abs(angle + (M_PI - diag)) < M_PI / 36)
        {
            normal = geometry_center.getVectorTo(ab->p1);
        }
        else if (std::abs(angle) < diag)
        {
            normal = geometry_center.getVectorTo(cd->getGeometryCenter());
        }
        else if (angle >= diag && angle <= M_PI - diag)
        {
            normal = geometry_center.getVectorTo(bc->getGeometryCenter());
        }
        else if (std::abs(angle) > M_PI - diag)
        {
            normal = geometry_center.getVectorTo(ab->getGeometryCenter());
        }
        else
        {
            normal = geometry_center.getVectorTo(da->getGeometryCenter());
        }
        return CrossingResult2D(true, collisionCenter, normal);
    }
}

CrossingResult2D Rectangle2D::cross(const Rectangle2D *rectangle) const
{
    Vector2D normal = Vector2D(0, 0);
    // Switch technology in action
    if (this->getHeight() + this->getWidth() > 200) {
        if (std::abs(getAngle()) < M_PI / 2) {
            normal = Vector2D(0, 1);
        } else {
            normal = Vector2D(1, 0);
        }
    } else if (rectangle->getHeight() + rectangle->getWidth() > 200) {
        return rectangle->cross(this);
    }
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
        return CrossingResult2D(false, Point2D(0, 0), Vector2D(0, 0));
    }
    else
    {
        x /= amount;
        y /= amount;
        Point2D ans(x, y);
        if (normal.getLength() == 0) {
            normal = this->getGeometryCenter().getVectorTo(rectangle->getGeometryCenter());
        }
        return CrossingResult2D(this->contains(ans) && rectangle->contains(ans), ans, normal);
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
