#ifndef MAIN_H
#define MAIN_H

#include <QtGlobal>
#include <QtSerialBus>
#include <QDebug>
#include <QTimer>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QImageReader>
#include <qqml.h>
#include <QObject>
// #include <QQuickView>
#include <QQmlEngine>
#include <QQmlPropertyMap>
#include <QProcess>

#include <csignal>

#include "link_generic_dash.h"

#define CAN_DEVICE "can0"
#define CAN_BAUD 1000000

#endif // MAIN_H
