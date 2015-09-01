#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T20:18:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    GLWidget.cpp

HEADERS  += \
    MainWindow.h \
    GLWidget.h

FORMS    += mainwindow.ui

LIBS     += -lglut -lGL -lGLU

# Icons are from:
#   http://www.flaticon.com/packs/extended-ui
#   http://www.flaticon.com/packs/educational-icons
#   http://www.flaticon.com/packs/icomoon-free-1
#   http://www.flaticon.com/packs/art-studio
#   http://www.flaticon.com/packs/tech-support
RESOURCES += icons.qrc
