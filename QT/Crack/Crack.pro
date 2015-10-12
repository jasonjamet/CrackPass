#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T10:40:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    research.cpp \
    Functions.cpp

HEADERS  += mainwindow.h \
    research.h \
    Functions.h

FORMS    += mainwindow.ui \
    research.ui

OTHER_FILES += \
    ../shadow
