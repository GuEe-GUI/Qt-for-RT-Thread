#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtPlugin>

#include <rtthread.h>

#include <stdlib.h>

Q_IMPORT_PLUGIN(QRTThreadFbIntegrationPlugin)
Q_IMPORT_PLUGIN(QEvdevMousePlugin)
Q_IMPORT_PLUGIN(QEvdevKeyboardPlugin)
Q_IMPORT_PLUGIN(QtQuick2Plugin)
Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)
Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
Q_IMPORT_PLUGIN(QtQuickControls2ImagineStylePlugin)

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);

    putenv(const_cast<char *>("QV4_FORCE_INTERPRETER=1"));
    putenv(const_cast<char *>("QT_QUICK_BACKEND=software"));
    putenv(const_cast<char *>("QSG_RENDER_LOOP=basic"));
    putenv(const_cast<char *>("QT_QPA_PLATFORM=rtthreadfb"));

    QQuickStyle::setStyle(QStringLiteral("Imagine"));

    int argc = 1;
    char applicationName[] = "quick-automotive";
    char *argv[] = { applicationName, nullptr };

    rt_kprintf("QUICK_AUTOMOTIVE_STAGE app\n");
    QGuiApplication app(argc, argv);
    QIcon::setThemeName(QStringLiteral("automotive"));
    rt_kprintf("QUICK_AUTOMOTIVE_STAGE engine\n");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/automotive.qml")));
    if (engine.rootObjects().isEmpty()) {
        rt_kprintf("QUICK_AUTOMOTIVE_FAIL\n");
        return;
    }

    rt_kprintf("QUICK_AUTOMOTIVE_STAGE visible\n");
    const int result = app.exec();
    rt_kprintf("QUICK_AUTOMOTIVE_EXIT %d\n", result);
}
