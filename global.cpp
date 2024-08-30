#include "global.h"

unsigned long millis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

bool checkFile(QString filename) {
    return QFile::exists(filename);
}

bool readFile(QString filename, QByteArray &contents) {
    QFile inFile(filename);
    if (!inFile.open(QIODevice::ReadOnly)) {
        qCritical() << "Critical: Unable to open" << filename << "for reading - reason:" << inFile.errorString();
        return false;
    }
    contents = inFile.readAll();
    inFile.close();
    return true;
}

bool writeFile(QString filename, QByteArray contents, bool append) {
    QFile outFile(filename);
    QIODevice::OpenMode fileMode = append ? (QIODevice::WriteOnly | QIODevice::Truncate) : (QIODevice::WriteOnly);
    if (!outFile.open(fileMode)) {
        qCritical() << "Critical: Unable to open" << filename << "for writing - reason:" << outFile.errorString();
        return false;
    }
    long long int bytes_written = outFile.write(contents);
    if (bytes_written != contents.length()) {
        qCritical() << "Critical: Unable to complete write to" << filename << "- reason:" << outFile.errorString();
        outFile.close();
        return false;
    }
    outFile.close();
    return true;
}
