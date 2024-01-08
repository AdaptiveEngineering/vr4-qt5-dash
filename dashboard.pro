TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .

QT += quick
QT += serialbus
QT += widgets

CONFIG += console

QML_IMPORT_NAME = com.adaptiveengineering.dashboard
QML_IMPORT_MAJOR_VERSION = 1

SOURCES += \
    link_generic_dash.cpp \
    main.cpp

RESOURCES += \
    dashboard.qrc

target.path = /usr/share/dashboard
INSTALLS += target

HEADERS += \
    link_generic_dash.h \
    main.h
