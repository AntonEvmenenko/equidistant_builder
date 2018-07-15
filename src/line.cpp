#include "line.h"

#include <QDebug>
#include "geometry.h"

Point projectPointOnLine(Point p, Line l)
{
    Line temp(p, Vector(l.a(), l.b()));

    QVector<Point> result = intersectionLineLine(l, temp);

    Q_ASSERT(result.size() == 1);

    return result.first();
}

Line::Line()
{

}

Line::Line(Point a, Point b)
{
    m_a = b.y() - a.y();
    m_b = a.x() - b.x();
    m_c = a.y() * b.x() - a.x() * b.y();
}

Line::Line(Point a, Vector v): Line(a, a + v)
{

}

Line::Line(Segment s): Line(s.a(), s.b())
{

}

double Line::a()
{
    return m_a;
}

double Line::b()
{
    return m_b;
}

double Line::c()
{
    return m_c;
}

bool Line::contains(Point p)
{
    return isZero(m_a * p.x() + m_b * p.y() + m_c);
}

Vector Line::unitGuidingVector()
{
    return Vector(m_a, m_b).rotate90CW().normalize();
}
