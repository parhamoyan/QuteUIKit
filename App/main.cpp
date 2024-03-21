#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qutecheckbox.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // qmlRegisterType<QuteCheckbox>("QuteUIKit", 1, 0, "QuteCheckbox");
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
