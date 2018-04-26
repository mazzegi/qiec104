#-------------------------------------------------
#
# Project created by QtCreator 2018-03-16T15:52:56
#
#-------------------------------------------------

QT       += network testlib
QT       -= gui

CONFIG(release){
    TARGET = ../lib/qiec104
}

CONFIG(debug){
    TARGET = ../lib/qiec104d
}

OBJECTS_DIR=objects
MOC_DIR=moc
RCC_DIR=rcc
UI_DIR=ui

TEMPLATE = lib
DEFINES += LIBQIEC104_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/error.cpp \
    src/qualifier.cpp \
    src/header.cpp \
    src/streamer.cpp \
    src/binary.cpp \
    src/config.cpp \
    src/messagecodec.cpp \
    src/endpoint.cpp \
    src/slave.cpp \
    src/slave_connection.cpp \
    src/connection.cpp \
    src/master_connection.cpp \
    src/master_connection_tls.cpp \
    src/slave_tls.cpp

HEADERS += \
        include/libqiec104.h \
    include/libqiec104_global.h \
    src/error.h \
    src/endpoint.h \
    src/protocol.h \
    src/time.hpp \
    src/qualifier.h \
    src/header.h \
    src/streamer.h \
    src/binary.h \
    src/config.h \
    src/processor.h \
    src/messagedef.h \
    src/messagecodec.h \
    src/slave.h \
    src/slave_connection.h \
    src/connection.h \
    src/master_connection.h \
    src/master_connection_tls.h \
    src/slave_tls.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
