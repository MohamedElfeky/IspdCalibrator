#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T16:03:41
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += serialport
QT += widgets
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hdtas_machine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES  -= UNICODE
QMAKE_CFLAGS +=
QMAKE_CXXFLAGS +=
DEFINES += HDTAS_PARSER_EXPORT
DEFINES += HDTAS_WINDOWS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    ../hdtasparser/hdtasparser/hdtasparser.cpp \
    ../hdtasparser/hdtasparser/protocol_data_parser.cpp \
    ../hdtasparser/hdtasparser/utility.cpp \
    tcp_worker.cpp \
    tcp_socket_thread.cpp \
    worker.cpp \
    delegation.cpp \
    dialog.cpp \
    login.cpp \
    selectview.cpp \
    generateid.cpp \
    common.cpp \
    header.cpp \
    checkispd.cpp \
    #uploaddb.cpp
    udp_worker.cpp \
    udp_socket_thread.cpp \
    udp_socket_object.cpp

HEADERS  += \
    tcp_worker.h \
    tcp_socket_thread.h \
    worker.h \
    delegation.h \
    ../hdtasparser/hdtasparser/hdtasparser.h \
    ../hdtasparser/hdtasparser/header.h \
    ../hdtasparser/hdtasparser/protocol_data_parser.h \
    ../hdtasparser/hdtasparser/struct.h \
    ../hdtasparser/hdtasparser/utility.h \
    common.h \
    dialog.h \
    login.h \
    selectview.h \
    generateid.h \
    header.h \
    checkispd.h \
    #uploaddb.h
    udp_worker.h \
    udp_socket_thread.h \
    udp_socket_object.h \
    pubdata.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog.ui \
    login.ui \
    selectview.ui \
    generateid.ui \
    checkispd.ui \
    #uploaddb.ui
    checkispd.ui

RESOURCES += \
    resource.qrc

RC_FILE = app.rc
