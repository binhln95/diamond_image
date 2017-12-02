#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T19:01:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_shape -lopencv_imgproc
SOURCES += main.cpp\
        mainwindow.cpp

QT += qml quick
HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    main.qml
