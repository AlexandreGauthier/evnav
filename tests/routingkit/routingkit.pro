#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T17:51:25
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_routingkit2test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += tst_routingkit2test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_CXXFLAGS += -I$${PWD}/../../3rdparty/RoutingKit/include
QMAKE_LFLAGS += -L$${PWD}/../../3rdparty/RoutingKit/lib

LIBS += -L$${PWD}/../../3rdparty/RoutingKit/lib -lroutingkit

DEFINES += TOPSRCDIR=\\\"\"$${top_srcdir}\"\\\"
