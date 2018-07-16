#include "geometry.h"

bool equal(double a, double b)
{
    return fabs(a - b) < eps;
}

bool equal(Point a, Point b)
{
    return equal(a.x(), b.x()) && equal(a.y(), b.y());
}

bool equal(Line l1, Line l2)
{
    double d = l1.a() * l2.b() - l2.a() * l1.b();
    double d1 = l2.c() * l1.b() - l1.c() * l2.b();
    double d2 = l2.a() * l1.c() - l1.a() * l2.c();

    return isZero(d) && isZero(d1) && isZero(d2);
}

bool isZero(double a)
{
    return equal(a, 0.0);
}

void removeEqualPoints(QVector<Point> &points)
{
    std::sort(points.begin(), points.end(), [](const Point &p1, const Point &p2){
        return Vector(p1.x(), p1.y()).length() > Vector(p2.x(), p2.y()).length();
    });

    auto last = std::unique(points.begin(), points.end(), [](const Point &p1, const Point &p2){
        return equal(p1, p2);
    });

    points.erase(last, points.end());
}

double distanceFromPointToLine(Point p, Line l)
{
    Point projection = projectPointOnLine(p, l);
    return Vector(p, projection).length();
}


Point projectPointOnLine(Point p, Line l)
{
    Line temp(p, Vector(l.a(), l.b()));

    QVector<Point> result = intersectionLineLine(l, temp);

    Q_ASSERT(result.size() == 1);

    return result.first();
}

QVector<Point> intersectionLineLine(Line l1, Line l2)
{
    QVector<Point> result;

    double d = l1.a() * l2.b() - l2.a() * l1.b();
    double d1 = l2.c() * l1.b() - l1.c() * l2.b();
    double d2 = l2.a() * l1.c() - l1.a() * l2.c();

    if (isZero(d) && isZero(d1) && isZero(d2)) {
        // conincidence
        // TODO
         Q_ASSERT(false);
    } else if (isZero(d) && (!isZero(d1) || !isZero(d2))) {
        // parallelism
        return result;
    }

    result.append(Point(d1 / d, d2 / d));
    return result;
}

QVector<Point> intersectionLineCircle(Line l, Circle c)
{
    QVector<Point> result;

    double distanceFromCenterToLine = distanceFromPointToLine(c.center(), l);

    if (equal(distanceFromCenterToLine, c.radius())) {
        result.append(projectPointOnLine(c.center(), l));
        return result;
    } else if (distanceFromCenterToLine > c.radius()) {
        return result;
    } else {
        // A, B -- intersection points
        double ab_2 = sqrt(c.radius() * c.radius() - distanceFromCenterToLine * distanceFromCenterToLine);
        Point p = projectPointOnLine(c.center(), l);
        Vector v = l.unitGuidingVector();
        result.append(p + v * ab_2);
        result.append(p + v * -ab_2);
        return result;
    }
}

QVector<Point> intersectionCircleCircle(Circle c1, Circle c2)
{
    QVector<Point> result;

    Vector o1o2 = Vector(c1.center(), c2.center());
    double distanceFromCenterToCenter = o1o2.length();

    if (isZero(distanceFromCenterToCenter) && equal(c1.radius(), c2.radius())) {
        // conincidence
        Q_ASSERT(false);
    }

    // A, B -- intersection points
    double d1 = (distanceFromCenterToCenter * distanceFromCenterToCenter - c2.radius() * c2.radius() + c1.radius() * c1.radius()) / (2 * distanceFromCenterToCenter);
    double temp = c1.radius() * c1.radius() - d1 * d1;

    if (isZero(temp)) {
        result.append(c1.center() + o1o2.normalize() * d1);
        return result;
    } else if (temp < 0) {
        return result;
    } else {

        double ab_2 = sqrt(temp);
        Point p = c1.center() + o1o2.normalize() * d1;
        Vector v = o1o2.normalize().rotate90CW();
        result.append(p + v * ab_2);
        result.append(p + v * -ab_2);
        return result;
    }
}

QVector<Point> intersectionSegmentSegment(Segment s1, Segment s2)
{
    QVector<Point> result;

    Line l1(s1), l2(s2);

    if (equal(l1, l2)) {
        // TODO
        return result;
    }

    QVector<Point> linesIntersection = intersectionLineLine(l1, l2);

    if (!linesIntersection.isEmpty()) {
        Point p = linesIntersection.first();
        if (s1.contains(p) && s2.contains(p)) {
            result.append(p);
        }
    }

    return result;
}

QVector<Point> intersectionSegmentArc(Segment s, Arc a)
{
    QVector<Point> result;
    QVector<Point> lineCircleIntersection = intersectionLineCircle(Line(s), Circle(a.center(), a.radius()));

    for (auto i = lineCircleIntersection.begin(); i != lineCircleIntersection.end(); ++i) {
        if (s.contains(*i) && a.contains(*i)) {
            result.append(*i);
        }
    }

    return result;
}

QVector<Point> intersectionSegmentCircle(Segment s, Circle c)
{
    QVector<Point> result;
    QVector<Point> lineCircleIntersection = intersectionLineCircle(Line(s), c);

    for (auto i = lineCircleIntersection.begin(); i != lineCircleIntersection.end(); ++i) {
        if (s.contains(*i)) {
            result.append(*i);
        }
    }

    return result;
}

QVector<Point> intersectionArcArc(Arc a1, Arc a2)
{
    QVector<Point> result;
    QVector<Point> circleCircleIntersection = intersectionCircleCircle(Circle(a1.center(), a1.radius()), Circle(a2.center(), a2.radius()));

    for (auto i = circleCircleIntersection.begin(); i != circleCircleIntersection.end(); ++i) {
        if (a1.contains(*i) && a2.contains(*i)) {
            result.append(*i);
        }
    }

    return result;
}

QVector<Point> intersectionArcCircle(Arc a, Circle c)
{
    QVector<Point> result;
    QVector<Point> circleCircleIntersection = intersectionCircleCircle(Circle(a.center(), a.radius()), c);

    for (auto i = circleCircleIntersection.begin(); i != circleCircleIntersection.end(); ++i) {
        if (a.contains(*i)) {
            result.append(*i);
        }
    }

    return result;
}

bool segmentInsideRectangle(Segment s, Rectangle r)
{
    QVector<Segment> rectangleEdges = r.edges();

    for (auto i = rectangleEdges.begin(); i != rectangleEdges.end(); ++i) {
        if (equal(Line(s), Line(*i))) {
            return false;
        }
    }

    if (r.inside(s.a()) || r.inside(s.b()) || r.inside(s.center())) {
        return true;
    }

    QVector<Point> intersectionPoints;
    for (auto i = rectangleEdges.begin(); i != rectangleEdges.end(); ++i) {
        intersectionPoints.append(intersectionSegmentSegment(s, *i));
    }

    removeEqualPoints(intersectionPoints);

    Q_ASSERT(intersectionPoints.size() < 3);

    return intersectionPoints.size() == 2;
}

bool arcInsideRectangle(Arc a, Rectangle r)
{
    // TODO: check

    if (r.inside(a.a()) || r.inside(a.b())) {
        return true;
    }

    QVector<Segment> rectangleEdges = r.edges();

    QVector<Point> intersectionPoints;
    for (auto i = rectangleEdges.begin(); i != rectangleEdges.end(); ++i) {
        intersectionPoints.append(intersectionSegmentArc(*i, a));
    }

    removeEqualPoints(intersectionPoints);

    Q_ASSERT(intersectionPoints.size() < 3);

    return (intersectionPoints.size() == 2) && r.inside(a.middlePoint());
}

bool segmentInsideCircle(Segment s, Circle c)
{
    if (c.inside(s.a()) || c.inside(s.b())) {
        return true;
    }

    // TODO: finish

    return false;
}

bool arcInsideCircle(Arc a, Circle c)
{
    if (c.inside(a.a()) || c.inside(a.b())) {
        return true;
    }

    // TODO: finish

    return false;
}
