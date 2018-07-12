#include "solver.h"

Solver::Solver()
{

}

void Solver::addPathPart(Segment segment)
{
    m_path.append(PathPart(segment));
}

void Solver::addPathPart(Arc arc)
{
    m_path.append(PathPart(arc));
}

QVector<PathPart>& Solver::getPath()
{
    return m_path;
}
