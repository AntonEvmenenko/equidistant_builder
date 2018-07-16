#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>
#include "pathpart.h"
#include "vector.h"
#include "geometry.h"
#include "rectangle.h"

class Solver
{
public:
    Solver();
    void addPathPart(Segment segment);
    void addPathPart(Arc arc);
    QVector<PathPart>& getOriginalPath();
    QVector<PathPart> getFirstOffsetPath();
    QVector<PathPart> getSecondOffsetPath();

    QVector<PathPart> offsetPathPart(PathPart pathPart);
    void makeOffset();
    void addCircles();

    int getOffset();
    void setOffset(int offset);

    void solve();
    void clear();

private:
    QVector<Point> getIntersectionPoints(PathPart a, PathPart b);

    QVector<PathPart> split(PathPart pathPart, QVector<Point> points);
    QVector<PathPart> splitSegment(Segment s, QVector<Point> points);
    QVector<PathPart> splitArc(Arc a, QVector<Point> points);
    QVector<PathPart> splitCircle(Circle c, QVector<Point> points);

    QVector<PathPart> m_originalPath;
    QVector<PathPart> m_firstOffsetPath;
    QVector<PathPart> m_secondOffsetPath;

    QVector<Rectangle> m_cutoffRectangles;
    QVector<Circle> m_cutoffCircles;

    int m_offset = 30;
};

#endif // SOLVER_H
