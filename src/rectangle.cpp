#include "rectangle.h"

#include "geometry.h"

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(Point center, Vector x, Vector y): m_center(center), m_x(x), m_y(y)
{

}

Point Rectangle::transformPointToLocalCoordinateSystem(Point p)
{
    p = Point(p.x() - m_center.x(), p.y() - m_center.y());

    Vector xn = Vector(m_x.x(), m_x.y()).normalize();
    Vector yn = Vector(m_y.x(), m_y.y()).normalize();

    return Point(xn.x() * p.x() + xn.y() * p.y(), yn.x() * p.x() + yn.y() * p.y());
}

bool Rectangle::contains(Point p)
{
    auto f = [](double x, double a, double b){
        return ((a < x || equal(a, x)) && (x < b || equal(x, b))) || ((a > x || equal(a, x)) && (x > b || equal(x, b)));
    };

    p = transformPointToLocalCoordinateSystem(p);

    double width_2 = m_x.length();
    double height_2 = m_y.length();

    return f(p.x(), -width_2, width_2) && f(p.y(), -height_2, height_2);
}

bool Rectangle::inside(Point p)
{
    auto f = [](double x, double a, double b){
        return ((a < x || equal(a, x)) && (x < b || equal(x, b))) || ((a > x || equal(a, x)) && (x > b || equal(x, b)));
    };

    p = transformPointToLocalCoordinateSystem(p);

    double width_2 = m_x.length();
    double height_2 = m_y.length();

    bool c = f(p.x(), -width_2, width_2) && f(p.y(), -height_2, height_2);

    if (!c) {
        return false;
    }

    bool onEdge = equal(p.x(), -width_2) || equal(p.x(), width_2) || equal(p.y(), -height_2) || equal(p.y(), height_2);

    return c && !onEdge;
}

QVector<Point> Rectangle::vertexesCCW() {
    QVector<Point> result;

    result.append(m_center + m_x + m_y);
    result.append(m_center + (m_x * -1) + m_y);
    result.append(m_center + (m_x * -1) + (m_y * -1));
    result.append(m_center + m_x + (m_y * -1));

    Point center = m_center;

    std::sort(result.begin(), result.end(), [center](const Point& p1, const Point& p2){
        return atan2(p1.y() - center.y(), p1.x() - center.x()) < atan2(p2.y() - center.y(), p2.x() - center.x());
    });

    return result;
}

QVector<Segment> Rectangle::edges()
{
    QVector<Point> vertexes = vertexesCCW();

    Q_ASSERT(vertexes.size() == 4);

    QVector<Segment> result;

    result.append(Segment(vertexes[0], vertexes[1]));
    result.append(Segment(vertexes[1], vertexes[2]));
    result.append(Segment(vertexes[2], vertexes[3]));
    result.append(Segment(vertexes[3], vertexes[0]));

    return result;
}
