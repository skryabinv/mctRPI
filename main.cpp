#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCursor>
#include "AppController.h"
#include "ManualModeController.h"
#include "OperatorModeController.h"
#include "SettingsModeController.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    app.setOverrideCursor(Qt::BlankCursor);

    AppController appController;
    QQmlApplicationEngine engine;

    qmlRegisterType<AppController>("AppController", 1, 0, "AppController");
    qmlRegisterType<ManualModeController>("ManualModeController", 1, 0, "ManualModeController");
    qmlRegisterType<OperatorModeController>("OperatorModeController", 1, 0, "OperatorModeController");
    qmlRegisterType<SettingsModeController>("SettingsModeController", 1, 0, "SettingsModeController");

    engine.rootContext()->setContextProperty("appController", &appController);
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
