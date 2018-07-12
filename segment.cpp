#include "segment.h"

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
