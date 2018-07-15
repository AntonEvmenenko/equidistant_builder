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
    src/main.cpp \
    src/mainwindow.cpp \
    src/point.cpp \
    src/vector.cpp \
    src/arc.cpp \
    src/pathpart.cpp \
    src/segment.cpp \
    src/solver.cpp \
    src/line.cpp \
    src/circle.cpp \
    src/geometry.cpp \
    src/rectangle.cpp

HEADERS += \
    src/mainwindow.h \
    src/point.h \
    src/vector.h \
    src/arc.h \
    src/pathpart.h \
    src/segment.h \
    src/solver.h \
    src/line.h \
    src/circle.h \
    src/geometry.h \
    src/rectangle.h

FORMS += \
    src/mainwindow.ui
