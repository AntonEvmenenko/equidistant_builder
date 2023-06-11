#ifndef POINT_H
#define POINT_H

//#include "vector.h"

class Point;
class Vector;

Point operator+(const Point &point, const Vector &vector);

class Point
{
public:
    Point();
    Point(double x, double y);

    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

private:
    double m_x, m_y;
};

#endif // POINT_H
