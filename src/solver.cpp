#include "solver.h"

Solver::Solver()
{

}

void Solver::addPathPart(Segment segment)
{
    m_originalPath.append(PathPart(segment));
}

void Solver::addPathPart(Arc arc)
{
    m_originalPath.append(PathPart(arc));
}

QVector<PathPart>& Solver::getOriginalPath()
{
    return m_originalPath;
}

QVector<PathPart> Solver::getOffsetPath()
{
    return m_firstOffsetPath;
}

QVector<PathPart> Solver::offsetPathPart(PathPart pathPart)
{
    QVector<PathPart> result;

    if (pathPart.type() == PathPartType::Segment) {
        Vector n = Vector(pathPart.segment().a(), pathPart.segment().b()).rotate90CW().normalize();

        m_firstOffsetPath.append(PathPart(Segment(pathPart.segment().a() + n * m_offset, pathPart.segment().b() + n * m_offset)));
        m_firstOffsetPath.append(PathPart(Segment(pathPart.segment().a() + n * -m_offset, pathPart.segment().b() + n * -m_offset)));
    } else if (pathPart.type() == PathPartType::Arc) {
        Vector n1 = Vector(pathPart.arc().a(), pathPart.arc().center()).normalize();
        Vector n2 = Vector(pathPart.arc().b(), pathPart.arc().center()).normalize();

        if (m_offset <= pathPart.arc().radius()) {
            m_firstOffsetPath.append(PathPart(Arc(pathPart.arc().a() + n1 * m_offset, pathPart.arc().b() + n2 * m_offset, pathPart.arc().center())));
        }
        m_firstOffsetPath.append(PathPart(Arc(pathPart.arc().a() + n1 * -m_offset, pathPart.arc().b() + n2 * -m_offset, pathPart.arc().center())));
    }

    return result;
}

void Solver::makeOffset()
{
    for (auto i = m_originalPath.begin(); i != m_originalPath.end(); ++i) {
        m_firstOffsetPath.append(offsetPathPart(*i));
    }
}

void Solver::addCircles()
{

}

void Solver::setOffset(int offset)
{
    m_offset = offset;
}

void Solver::solve()
{
    makeOffset();
    addCircles();
}

void Solver::clear()
{
    m_firstOffsetPath.clear();
}
