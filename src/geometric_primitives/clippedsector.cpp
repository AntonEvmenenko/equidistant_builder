#include "clippedsector.h"

#include "segment.h"
#include "geometry.h"

ClippedSector::ClippedSector()
{

}

ClippedSector::ClippedSector(Arc inArc, Arc outArc): m_inArc(inArc), m_outArc(outArc)
{

}

bool ClippedSector::onEdge(Point p)
{
    Segment s1(m_inArc.a(), m_outArc.a());
    Segment s2(m_inArc.b(), m_outArc.b());

    return s1.contains(p) || s2.contains(p) || m_inArc.contains(p) || m_outArc.contains(p);
}

bool ClippedSector::inside(Point p)
{
    if (onEdge(p)) {
        return false;
    }

    double inRadius = m_inArc.radius();
    double outRadius = m_outArc.radius();

    double pointRadius = Vector(m_inArc.center(), p).length();

    if (!(pointRadius > inRadius && pointRadius < outRadius)) {
        return false;
    }

    Segment s(m_inArc.center(), p);

    return !intersectionSegmentArc(s, m_inArc).isEmpty();
}
