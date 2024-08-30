#ifndef GLOBAL_H
#define GLOBAL_H

// Keep in mind, anything you include here gets included
// by any and every other file that includes this file
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QFlag>
#include <QString>
#include <QByteArray>
#include <chrono>

// Get milliseconds since uptime
unsigned long millis();

// Check if file exists
bool checkFile(QString filename);

// Read from a file
bool readFile(QString filename, QByteArray &contents);

// Write to a file
bool writeFile(QString filename, QByteArray contents, bool append = false);

#endif // GLOBAL_H
