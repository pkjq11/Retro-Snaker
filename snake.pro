#-------------------------------------------------
#
# Project created by QtCreator 2012-12-11T19:56:10
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    food.cpp \
    snake.cpp \
    controller.cpp \
    controlpanel.cpp \
    startwidget.cpp \
    rankdialog.cpp \
    graphicsitemdecorator.cpp \
    wall.cpp

HEADERS  += mainwindow.h \
    food.h \
    constants.h \
    snake.h \
    controller.h \
    controlpanel.h \
    startwidget.h \
    rankdialog.h \
    graphicsitemdecorator.h \
    wall.h

RESOURCES += \
    res.qrc
