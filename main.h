#ifndef MAIN_H
#define MAIN_H

#include <QtGlobal>
#include <QtSerialBus>
#include <QDebug>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QFontDatabase>

#include <QTimer>
#include <QQmlContext>
#include <QFont>
#include <QImageReader>
#include <qqml.h>
#include <QObject>
// #include <QQuickView>
#include <QQmlEngine>
#include <QProcess>

#include <csignal>

#include "config.h"
#include "global.h"
#include "link_generic_dash.h"
#include "gpio.h"
#include "processor.h"

// Keep no matter what
#include <QQmlPropertyMap>
QQmlPropertyMap dummy;

#endif // MAIN_H
