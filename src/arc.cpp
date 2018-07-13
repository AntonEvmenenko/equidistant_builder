#include "arc.h"

#include "vector.h"
#include "line.h"

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
