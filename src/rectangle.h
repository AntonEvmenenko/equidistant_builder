#ifndef RECTANGLE_H
#define RECTANGLE_H

//          ^ m_y
//          |
//          |
//          *-----> m_x
//      m_center

#include <QVector>

#include "point.h"
#include "vector.h"
#include "segment.h"
#include "arc.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(Point center, Vector x, Vector y);

    Point transformPointToLocalCoordinateSystem(Point p);

    // point inside or on edge
    bool contains(Point p);

    // point ONLY inside
    bool inside(Point p);

    QVector<Point> vertexesCCW();
    QVector<Segment> edges();

private:
    Point m_center;
    Vector m_x, m_y;
};

#endif // RECTANGLE_H
