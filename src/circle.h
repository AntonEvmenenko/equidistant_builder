#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"

class Circle
{
public:
    Circle();
    Circle(Point center, double radius);

private:
    Point m_center;
    double m_radius;
};

#endif // CIRCLE_H
