#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T20:02:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = equidistant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/geometric_primitives/arc.cpp \
    src/geometric_primitives/circle.cpp \
    src/geometric_primitives/clippedsector.cpp \
    src/geometric_primitives/line.cpp \
    src/geometric_primitives/point.cpp \
    src/geometric_primitives/rectangle.cpp \
    src/geometric_primitives/sector.cpp \
    src/geometric_primitives/segment.cpp \
    src/geometric_primitives/vector.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pathpart.cpp \
    src/solver.cpp \
    src/geometry.cpp

HEADERS += \
    src/geometric_primitives/arc.h \
    src/geometric_primitives/circle.h \
    src/geometric_primitives/clippedsector.h \
    src/geometric_primitives/line.h \
    src/geometric_primitives/point.h \
    src/geometric_primitives/rectangle.h \
    src/geometric_primitives/sector.h \
    src/geometric_primitives/segment.h \
    src/geometric_primitives/vector.h \
    src/main.h \
    src/mainwindow.h \
    src/pathpart.h \
    src/solver.h \
    src/geometry.h

FORMS += \
    src/mainwindow.ui
