#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T14:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacMan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    level.cpp \
    gameobject.cpp \
    wall.cpp \
    coin.cpp \
    supercoin.cpp \
    movingobject.cpp \
    pacman.cpp \
    ghost.cpp

HEADERS  += mainwindow.h \
    level.h \
    gameobject.h \
    wall.h \
    coin.h \
    supercoin.h \
    movingobject.h \
    pacman.h \
    ghost.h

RESOURCES += \
    res.qrc

DISTFILES += \
    pacman.rc

RC_FILE = pacman.rc

FORMS +=
