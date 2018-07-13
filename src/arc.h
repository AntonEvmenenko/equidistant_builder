#ifndef ARC_H
#define ARC_H

#include "point.h"

enum class ArcDirection
{
    CW,
    CCW
};

class Arc
{
public:
    Arc();
    Arc(Point a, Point b, Point center, ArcDirection direction);
    Arc(Point a, Point b, Point center);

    Point& a();
    Point& b();
    Point& center();

    ArcDirection arcDirection();

    double radius();
    void updateCenter();
    void changeDirection();

private:
    Point m_a;
    Point m_b;
    Point m_center;

    ArcDirection m_arcDirection;
};

#endif // ARC_H
