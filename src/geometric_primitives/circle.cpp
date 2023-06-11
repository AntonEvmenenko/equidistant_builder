#include "circle.h"

#include "geometry.h"

Circle::Circle()
{

}

Circle::Circle(Point center, double radius): m_center(center), m_radius(radius)
{

}

Point Circle::center()
{
    return m_center;
}

double Circle::radius()
{
    return m_radius;
}

bool Circle::onEdge(Point p)
{
    return equal(Vector(m_center, p).length(), m_radius);
}

bool Circle::inside(Point p)
{
    return (Vector(m_center, p).length() < m_radius) && !onEdge(p);
}
