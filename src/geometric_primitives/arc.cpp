#include "arc.h"

#include <QDebug>

#include "vector.h"
#include "line.h"
#include "circle.h"
#include "geometry.h"

Arc::Arc()
{

}

Arc::Arc(Point a, Point b, Point center, ArcDirection direction): m_a(a), m_b(b), m_center(center), m_arcDirection(direction)
{

}


Arc::Arc(Point a, Point b, Point center): Arc(a, b, center, ArcDirection::CW)
{

}

Point& Arc::a()
{
    return m_a;
}

Point &Arc::b()
{
    return m_b;
}

Point &Arc::center()
{
    return m_center;
}

ArcDirection Arc::arcDirection()
{
    return m_arcDirection;
}

double Arc::radius()
{
    return Vector(m_a, center()).length();
}

void Arc::updateCenter()
{
    Vector ab(m_a, m_b);
    m_center = projectPointOnLine(m_center, Line(m_a + ab * 0.5, ab.rotate90CW()));
}

void Arc::changeDirection()
{
    if (m_arcDirection == ArcDirection::CW) {
        m_arcDirection = ArcDirection::CCW;
    } else {
        m_arcDirection = ArcDirection::CW;
    }
}

bool Arc::contains(Point p)
{
    if (equal(m_a, p) || equal(m_b, p)) {
        return true;
    }

    if (!Circle(m_center, radius()).onEdge(p)) {
        return false;
    }

    Vector oa(m_center, m_a);
    Vector ob(m_center, m_b);
    Vector op(m_center, p);

    double a = oa ^ op;
    double b = op ^ ob;
    double c = oa ^ ob;

    bool result = (c >= 0 && !((a >= 0) & (b >= 0))) ||
                  (c <= 0 && ((a <= 0) & (b <= 0)));

    if (m_arcDirection == ArcDirection::CCW) {
        result = !result;
    }

    return result;
}


Point Arc::middlePoint()
{
    double startAngle = atan2(m_a.y() - m_center.y(), m_a.x() - m_center.x());
    double endAngle = atan2(m_b.y() - m_center.y(), m_b.x() - m_center.x());

    if (m_arcDirection == ArcDirection::CCW) {
        if (endAngle < startAngle) {
            endAngle += 2 * M_PI;
        }

        double spanAngle = endAngle - startAngle;
        double angle = startAngle + spanAngle * 0.5;

        return m_center + Vector(cos(angle) * radius(), sin(angle) * radius());
    } else {
        if (endAngle > startAngle) {
            endAngle -= 2 * M_PI;
        }

        double spanAngle = startAngle - endAngle;
        double angle = startAngle - spanAngle * 0.5;

        return m_center + Vector(cos(angle) * radius(), sin(angle) * radius());
    }
}
