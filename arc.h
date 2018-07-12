#ifndef ARC_H
#define ARC_H

#include "point.h"

class Arc
{
public:
    Arc();
    Arc(Point a, Point b, Point c);

    Point& a();
    Point& b();
    Point& c();
    Point center();

    double radius();

private:
    // a -> b -> c
    Point m_a;
    Point m_b;
    Point m_c;
};

#endif // ARC_H
