QT -= gui
QT += network

CONFIG(release){
    TARGET = ../bin/qiec104-slave
    LIBS += -L$$OUT_PWD/../lib -lqiec104
}

CONFIG(debug){
    TARGET = ../bin/qiec104-slaved
    LIBS += -L$$OUT_PWD/../lib/ -lqiec104d
}

OBJECTS_DIR=objects
MOC_DIR=moc
RCC_DIR=rcc
UI_DIR=ui

CONFIG += c++11 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../libqiec104/include

SOURCES += main.cpp
