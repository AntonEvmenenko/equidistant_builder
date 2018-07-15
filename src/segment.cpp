#include "segment.h"

#include "line.h"
#include "geometry.h"

Segment::Segment()
{

}

Segment::Segment(Point a, Point b): m_a(a), m_b(b)
{

}

Point& Segment::a()
{
    return m_a;
}

Point& Segment::b()
{
    return m_b;
}

bool Segment::contains(Point p)
{
    Line l(m_a, m_b);

    auto f = [](double x, double a, double b){
        return ((a < x || equal(a, x)) && (x < b || equal(x, b))) || ((a > x || equal(a, x)) && (x > b || equal(x, b)));
    };

    return (l.contains(p) && f(p.x(), m_a.x(), m_b.x()) && f(p.y(), m_a.y(), m_b.y())) ||
            equal(p, m_a) ||
            equal(p, m_b);
}
