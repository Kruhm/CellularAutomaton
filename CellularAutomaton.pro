#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T19:28:36
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CellularAutomaton
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

SOURCES += main.cpp \
        cabase.cpp \
        gameoflife.cpp \
        gamefield.cpp \
        snake.cpp \
        snakeBodyPart.cpp \
        cell.cpp \
    predatorprey.cpp

HEADERS += cabase.h \
        gameoflife.h \
        gamefield.h \
        snake.h \
        snakeBodyPart.h \
        cell.h \
    predatorprey.h
