#ifndef ARC_H
#define ARC_H

#include "point.h"

class Arc
{
public:
    Arc();
    Arc(Point a, Point b, Point center);

    Point& a();
    Point& b();
    Point& center();

    double radius();

private:
    // По часовой стрелке от a к b вокруг center
    Point m_a;
    Point m_b;
    Point m_center;
};

#endif // ARC_H
