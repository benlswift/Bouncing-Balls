#-------------------------------------------------
#
# Project created by QtCreator 2019-11-23T14:13:35
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lglut -lGLU

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bouncingBalls
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logo.cpp \
    glwidget.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    logo.h \
    glwidget.h \
    window.h
