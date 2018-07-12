#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Point a(10, 10);
    Point b(50, 10);
    Point center(30, 30);

    Point c(100, 100);

    m_solver.addPathPart(Arc(a, b, center));
    m_solver.addPathPart(Segment(b, c));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug() << "Paint event";

    Q_UNUSED(event);
    QPainter painter(this);

    QVector<PathPart>& path = m_solver.getPath();

    for (auto i = path.begin(); i < path.end(); ++i) {
        if (i->type() == PathPartType::Arc) {
            drawArc(i->arc(), Qt::black, 1, &painter);
        } else if (i->type() == PathPartType::Segment) {
            drawSegment(i->segment(), Qt::black, 1, &painter);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Point p = Point(event->x(), event->y());

    qDebug() << p.x() << p.y();

    QVector<PathPart>& path = m_solver.getPath();

    const double eps = 5;

    for (auto i = path.begin(); i < path.end(); ++i) {
        if (i->type() == PathPartType::Segment) {
            if (Vector(p, i->segment().a()).length() < eps) {
                m_dragPoints.append(&(i->segment().a()));
            } else if (Vector(p, i->segment().b()).length() < eps) {
                m_dragPoints.append(&(i->segment().b()));
            }
        } else if (i->type() == PathPartType::Arc) {
            if (Vector(p, i->arc().a()).length() < eps) {
                m_dragPoints.append(&(i->arc().a()));
            } else if (Vector(p, i->arc().b()).length() < eps) {
                m_dragPoints.append(&(i->arc().b()));
            } else if (Vector(p, i->arc().center()).length() < eps) {
                m_dragPoints.append(&(i->arc().center()));
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_dragPoints.clear();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_dragPoints.isEmpty()) {
        qDebug() << "aaa";

        for (auto i = m_dragPoints.begin(); i != m_dragPoints.end(); ++i) {
            (*i)->setX(event->x());
            (*i)->setY(event->y());
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

    painter->drawPoint(QPointF(point.x(), point.y()));
}

void MainWindow::drawArc(Arc arc, int width, QColor color, QPainter* painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    double radius = arc.radius();
    QRectF rectangle(arc.center().x() - radius, arc.center().y() - radius, 2 * radius, 2 * radius);

    double startAngle = -atan2(arc.b().y() - arc.center().y(), arc.b().x() - arc.center().x()) * 180. / M_PI * 16;
    double endAngle = -atan2(arc.a().y() - arc.center().y(), arc.a().x() - arc.center().x()) * 180. / M_PI * 16;

    painter->drawArc(rectangle, startAngle, endAngle - startAngle);

    drawPoint(arc.a(), 3, Qt::red, painter);
    drawPoint(arc.b(), 3, Qt::red, painter);
    drawPoint(arc.center(), 3, Qt::green, painter);
}

void MainWindow::drawSegment(Segment segment, int width, QColor color, QPainter *painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    painter->drawLine(segment.a().x(), segment.a().y(), segment.b().x(), segment.b().y());

    drawPoint(segment.a(), 3, Qt::red, painter);
    drawPoint(segment.b(), 3, Qt::red, painter);
}
