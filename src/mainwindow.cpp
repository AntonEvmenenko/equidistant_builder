#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#define SEGMENT_WIDTH 2
#define SEGMENT_COLOR Qt::blue

#define ARC_WIDTH 2
#define ARC_COLOR Qt::blue

#define POINT_WIDTH 5
#define POINT_COLOR Qt::red

#define ARC_CENTER_WIDTH 5
#define ARC_CENTER_COLOR Qt::green

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<PathPart>& path = m_solver.getPath();

    for (auto i = path.begin(); i < path.end(); ++i) {
        if (i->type() == PathPartType::Arc) {
            i->arc().updateCenter();
            drawArc(i->arc(), ARC_WIDTH, ARC_COLOR, &painter);
        } else if (i->type() == PathPartType::Segment) {
            drawSegment(i->segment(), SEGMENT_WIDTH, SEGMENT_COLOR, &painter);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Point p = translatePoint(Point(event->x(), event->y()));

    const double eps = 5;

    QVector<PathPart>& path = m_solver.getPath();

    if (event->buttons() & Qt::LeftButton) {
        for (auto i = path.begin(); i < path.end(); ++i) {
            if (i->type() == PathPartType::Segment) {
                if (Vector(p, i->segment().a()).length() < eps) {
                    m_dragPoints.append(&(i->segment().a()));
                } else if (Vector(p, i->segment().b()).length() < eps) {
                    m_dragPoints.append(&(i->segment().b()));
                }
            } else {
                if (Vector(p, i->arc().a()).length() < eps) {
                    m_dragPoints.append(&(i->arc().a()));
                } else if (Vector(p, i->arc().b()).length() < eps) {
                    m_dragPoints.append(&(i->arc().b()));
                } else if (Vector(p, i->arc().center()).length() < eps) {
                    m_dragPoints.append(&(i->arc().center()));
                }
            }
        }
    } else if (event->buttons() & Qt::RightButton) {
        for (auto i = path.begin(); i < path.end(); ++i) {
            if (i->type() == PathPartType::Arc) {
                if (Vector(p, i->arc().center()).length() < eps) {
                    i->arc().changeDirection();
                }
            }
        }
    }

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_dragPoints.clear();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    Point p = translatePoint(Point(event->x(), event->y()));

    if (!m_dragPoints.isEmpty()) {
        for (auto i = m_dragPoints.begin(); i != m_dragPoints.end(); ++i) {
            (*i)->setX(p.x());
            (*i)->setY(p.y());
        }
    }
    repaint();
}

void MainWindow::drawPoint(Point point, int width, QColor color, QPainter *painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    Point p = translatePoint(point);

    painter->drawPoint(QPointF(p.x(), p.y()));
}

void MainWindow::drawArc(Arc arc, int width, QColor color, QPainter* painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    double radius = arc.radius();

    Point p(arc.center().x() - radius, arc.center().y() - radius);
    p = translatePoint(p);

    QRectF rectangle(p.x(), p.y() - 2 * radius, 2 * radius, 2 * radius);

    double startAngle = atan2(arc.a().y() - arc.center().y(), arc.a().x() - arc.center().x()) * 180. / M_PI;
    double endAngle = atan2(arc.b().y() - arc.center().y(), arc.b().x() - arc.center().x()) * 180. / M_PI;
    double spanAngle = endAngle - startAngle;

    if (arc.arcDirection() == ArcDirection::CW && spanAngle > 0) spanAngle -= 360.;
    if (arc.arcDirection() == ArcDirection::CCW && spanAngle < 0) spanAngle += 360.;

    startAngle *= 16.;
    endAngle *= 16.;
    spanAngle *= 16.;

    painter->drawArc(rectangle, startAngle, spanAngle);

    drawPoint(arc.a(), POINT_WIDTH, POINT_COLOR, painter);
    drawPoint(arc.b(), POINT_WIDTH, POINT_COLOR, painter);
    drawPoint(arc.center(), ARC_CENTER_WIDTH, ARC_CENTER_COLOR, painter);
}

void MainWindow::drawSegment(Segment segment, int width, QColor color, QPainter *painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    Point a = translatePoint(segment.a());
    Point b = translatePoint(segment.b());

    painter->drawLine(a.x(), a.y(), b.x(), b.y());

    drawPoint(segment.a(), POINT_WIDTH, POINT_COLOR, painter);
    drawPoint(segment.b(), POINT_WIDTH, POINT_COLOR, painter);
}

Point MainWindow::getLastPathPoint()
{
    if (m_solver.getPath().isEmpty()) {
        return Point(200, 200);
    }

    PathPart lastPathPart = m_solver.getPath().last();

    Point p;
    if (lastPathPart.type() == PathPartType::Segment) {
        p = lastPathPart.segment().b();
    } else {
        p = lastPathPart.arc().b();
    }

    return p;
}

Point MainWindow::translatePoint(Point p)
{
    return Point(p.x(), this->height() - p.y());
}

void MainWindow::on_addSegmentButton_clicked()
{
    Point lastPoint = getLastPathPoint();

    m_solver.addPathPart(Segment(lastPoint, lastPoint + Vector(100, 0)));

    repaint();
}

void MainWindow::on_addArcButton_clicked()
{
    Point lastPoint = getLastPathPoint();

    m_solver.addPathPart(Arc(lastPoint, lastPoint + Vector(70, 0), lastPoint + Vector(70, 70)));

    repaint();
}
