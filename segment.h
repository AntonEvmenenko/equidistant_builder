#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment
{
public:
    Segment();
    Segment(Point a, Point b);

    Point& a();
    Point& b();

private:
    Point m_a;
    Point m_b;
};

#endif // SEGMENT_H
