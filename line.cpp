#include "line.h"

Point intersection(Line l1, Line l2)
{
    // TODO: add checks for parallelism / coincidence

    double d = l1.a() * l2.b() - l2.a() * l1.b();
    double d1 = l2.c() * l1.b() - l1.c() * l2.b();
    double d2 = l2.a() * l1.c() - l1.a() * l2.c();

    if (d == 0 && d1 == 0 && d2 == 0) {
        // coincidence
    } else if (d == 0 && (d1 != 0 || d2 != 0)) {
        // parallelism
    } else {
        return Point(d1 / d, d2 / d);
    }
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
