#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>
#include "pathpart.h"
#include "vector.h"

class Solver
{
public:
    Solver();
    void addPathPart(Segment segment);
    void addPathPart(Arc arc);
    QVector<PathPart>& getOriginalPath();
    QVector<PathPart> getOffsetPath();

    QVector<PathPart> offsetPathPart(PathPart pathPart);
    void makeOffset();
    void addCircles();

    void setOffset(int offset);

    void solve();
    void clear();

private:
    QVector<PathPart> m_originalPath;
    QVector<PathPart> m_firstOffsetPath;

    int m_offset = 10;
};

#endif // SOLVER_H
