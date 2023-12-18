#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtGui/QImageReader>

int main(int argc, char *argv[])
{
    QGuiApplication::setSetuidAllowed(true);
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VR4.ttf");
    QFontDatabase::addApplicationFont(":/fonts/7seg.otf");

    app.setFont(QFont("DejaVu Sans"));

    QQmlApplicationEngine engine(QUrl("qrc:/qml/dashboard.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
