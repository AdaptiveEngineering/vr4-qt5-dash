TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .
QT += quick

SOURCES += \
    main.cpp

RESOURCES += \
    dashboard.qrc

target.path = /usr/share/dashboard
INSTALLS += target
