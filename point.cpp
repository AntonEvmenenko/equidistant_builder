#include "point.h"

Point::Point()
{

}

Point::Point(double x, double y): m_x(x), m_y(y)
{
}

double Point::x()
{
    return m_x;
}

double Point::y()
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
