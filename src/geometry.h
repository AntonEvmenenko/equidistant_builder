#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "segment.h"
#include "arc.h"

const double eps = 1e-5;

bool equal(double a, double b);
bool equal(Point a, Point b);
bool isZero(double a);

double distanceFromPointToLine(Point p, Line l);

QVector<Point> intersectionLineLine(Line l1, Line l2);
QVector<Point> intersectionLineCircle(Line l, Circle c);
QVector<Point> intersectionCircleCircle(Circle c1, Circle c2);

QVector<Point> intersectionSegmentSegment(Segment s1, Segment s2);
QVector<Point> intersectionSegmentArc(Segment s, Arc a);
QVector<Point> intersectionSegmentCircle(Segment s, Circle c);
QVector<Point> intersectionArcArc(Arc a1, Arc a2);
QVector<Point> intersectionArcCircle(Arc a, Circle c);


#endif // GEOMETRY_H
