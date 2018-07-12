#ifndef SOLVER_H
#define SOLVER_H

#include <QVector>
#include <pathpart.h>
#include "vector.h"

class Solver
{
public:
    Solver();
    void addPathPart(Segment segment);
    void addPathPart(Arc arc);
    QVector<PathPart>& getPath();

private:
    QVector<PathPart> m_path;
};

#endif // SOLVER_H
