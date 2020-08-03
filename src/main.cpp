#include <QtGui>
#include <QtCore>
#include <QtQml>
#include <QtQuickControls2>
#ifdef Q_OS_ANDROID
#include <QtAndroid>

void permissionCallback(const QtAndroid::PermissionResultMap &res) {
    if (res["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
        QGuiApplication::exit();
}

#endif

#include "playlistmodel.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissions({QString("android.permission.READ_EXTERNAL_STORAGE")}, permissionCallback);
#endif

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<PlaylistModel>("PlaylistModel", 1, 0, "PlaylistModel");
    engine.load(url);

    return app.exec();
}
