#include "sector.h"

#include "geometry.h"

Sector::Sector()
{

}

Sector::Sector(Arc a): m_arc(a)
{

}

bool Sector::onEdge(Point p)
{
    if (equal(p, m_arc.center())) {
        return true;
    }

    Segment s1(m_arc.a(), m_arc.center());
    Segment s2(m_arc.b(), m_arc.center());

    return s1.contains(p) || s2.contains(p) || m_arc.contains(p);
}

bool Sector::inside(Point p)
{
    if (onEdge(p)) {
        return false;
    }

    double outRadius = m_arc.radius();

    double pointRadius = Vector(m_arc.center(), p).length();

    if (pointRadius > outRadius) {
        return false;
    }

    Vector v = Vector(m_arc.center(), p).normalize() * m_arc.radius();
    Segment s(m_arc.center(), m_arc.center() + v);

    return !intersectionSegmentArc(s, m_arc).isEmpty();
}
