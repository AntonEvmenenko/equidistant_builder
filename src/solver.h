#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>
#include "pathpart.h"
#include "vector.h"
#include "geometry.h"
#include "rectangle.h"
#include "clippedsector.h"

class Solver
{
public:
    Solver();
    void addPathPart(Segment segment);
    void addPathPart(Arc arc);
    QVector<PathPart>& getOriginalPath();
    QVector<PathPart> getOffsettedPath();
    QVector<PathPart> getSplittedPath();
    QVector<PathPart> getCutoffedPath();

    QVector<PathPart> offsetPathPart(PathPart pathPart);
    void makeOffset();
    void addCircles();
    void split();
    void cutoff();

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
    QVector<PathPart> m_offsetedPath;
    QVector<PathPart> m_splittedPath;
    QVector<PathPart> m_cutoffedPath;

    QVector<Rectangle> m_cutoffRectangles;
    QVector<Circle> m_cutoffCircles;
    QVector<ClippedSector> m_cutoffClippedSectors;
    QVector<Sector> m_cutoffSectors;

    int m_offset = 30;
};

#endif // SOLVER_H
