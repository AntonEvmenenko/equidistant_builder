#include "solver.h"

#include <QSet>
#include <QDebug>
#include <QtAlgorithms>

#include "geometry.h"

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

QVector<PathPart> Solver::getFirstOffsetPath()
{
    return m_firstOffsetPath;
}

QVector<PathPart> Solver::getSecondOffsetPath()
{
    return m_secondOffsetPath;
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
    for (auto i = m_originalPath.begin(); i != m_originalPath.end(); ++i) {
        if (i->type() == PathPartType::Segment) {
            m_firstOffsetPath.append(PathPart(Circle(i->segment().a(), m_offset)));
        } else if (i->type() == PathPartType::Arc) {
            m_firstOffsetPath.append(PathPart(Circle(i->arc().a(), m_offset)));
        }
    }

    if (m_originalPath.last().type() == PathPartType::Segment) {
        m_firstOffsetPath.append(PathPart(Circle(m_originalPath.last().segment().b(), m_offset)));
    } else if (m_originalPath.last().type() == PathPartType::Arc) {
        m_firstOffsetPath.append(PathPart(Circle(m_originalPath.last().arc().b(), m_offset)));
    }
}

int Solver::getOffset()
{
    return m_offset;
}

void Solver::setOffset(int offset)
{
    m_offset = offset;
}

void Solver::solve()
{
    makeOffset();
    addCircles();

    QVector<PathPart> in, out;
    in = m_firstOffsetPath;

    for (int i = 0; i < in.size(); ++i) {
        QVector<Point> intersectionPoints;
        for (int j = 0; j < in.size(); ++j) {
            if (i != j) {
                QVector<Point> temp = getIntersectionPoints(in[i], in[j]);
                for (auto p = temp.begin(); p != temp.end(); ++p) {
                    insertPointIfDoesntExist(*p, intersectionPoints);
                }
            }
        }

        if (!intersectionPoints.isEmpty()) {
            out.append(split(in[i], intersectionPoints));
        } else {
            out.append(in[i]);
        }
    }

    m_secondOffsetPath = out;
}

void Solver::clear()
{
    m_firstOffsetPath.clear();
}

QVector<Point> Solver::getIntersectionPoints(PathPart a, PathPart b)
{
    QVector<Point> result;

    if (a.type() == PathPartType::Segment && b.type() == PathPartType::Segment) {
        result = intersectionSegmentSegment(a.segment(), b.segment());
    }

    return result;
}

void Solver::insertPointIfDoesntExist(Point p, QVector<Point> &points)
{
    bool found = false;

    for (auto i = points.begin(); i != points.end(); ++i) {
        if (equal(p, *i)) {
            found = true;
            break;
        }
    }

    if (!found) {
        points.append(p);
    }
}

QVector<PathPart> Solver::split(PathPart pathPart, QVector<Point> points)
{
    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    if (pathPart.type() == PathPartType::Segment) {
        result = splitSegment(pathPart.segment(), points);
    }

    return result;
}

QVector<PathPart> Solver::splitSegment(Segment s, QVector<Point> points)
{
    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    auto i = points.begin();

    while (i != points.end()) {
        if (equal(*i, s.a()) || equal(*i, s.b())) {
            i = points.erase(i);
        } else {
            ++i;
        }
    }

    points.append(s.a());
    points.append(s.b());

    Point a = s.a();

    std::sort(points.begin(), points.end(), [a](const Point &p1, const Point &p2){
       return Vector(a, p1).length() < Vector(a, p2).length();
    });

    for (int i = 0; i < points.size() - 1; ++i) {
        result.append(PathPart(Segment(points[i], points[i + 1])));
    }

    return result;
}
