#include "point.h"

#include "vector.h"

Point::Point()
{

}

Point::Point(double x, double y): m_x(x), m_y(y)
{
}

double Point::x() const
{
    return m_x;
}

double Point::y() const
{
    return m_y;
}

void Point::setX(double x)
{
    m_x = x;
}

void Point::setY(double y)
{
    m_y = y;
}

Point operator+(const Point &point, const Vector &vector)
{
    return Point(point.x() + vector.x(), point.y() + vector.y());
}
