#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QtPlugin>

#include <rtthread.h>

#include <stdlib.h>

#ifndef QT_RTTHREAD_PACKAGE_MANAGED_PLUGINS
Q_IMPORT_PLUGIN(QRTThreadFbIntegrationPlugin)
Q_IMPORT_PLUGIN(QtQuick2Plugin)
Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)
Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
Q_IMPORT_PLUGIN(QtQuickControls2FusionStylePlugin)
Q_IMPORT_PLUGIN(QtQuickControls2MaterialStylePlugin)
Q_IMPORT_PLUGIN(QtQuickControls2UniversalStylePlugin)
Q_IMPORT_PLUGIN(QmlSettingsPlugin)
#endif

static void initResources()
{
    Q_INIT_RESOURCE(qmake_gallery_resources);
    Q_INIT_RESOURCE(qmake_font_resources);
}

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);
    initResources();

    putenv(const_cast<char *>("QV4_FORCE_INTERPRETER=1"));
    putenv(const_cast<char *>("QT_QUICK_BACKEND=software"));
    putenv(const_cast<char *>("QSG_RENDER_LOOP=basic"));
    putenv(const_cast<char *>("QT_QPA_PLATFORM=rtthreadfb"));

    QQuickStyle::setStyle(QStringLiteral("Fusion"));
    QGuiApplication::setApplicationName(QStringLiteral("Gallery"));
    QGuiApplication::setOrganizationName(QStringLiteral("QtProject"));

    int argc = 1;
    char applicationName[] = "quick-gallery";
    char *argv[] = { applicationName, nullptr };

    rt_kprintf("QUICK_GALLERY_STAGE app\n");
    QGuiApplication app(argc, argv);

    const int fontId = QFontDatabase::addApplicationFont(
                QStringLiteral(":/fonts/DejaVuSans.ttf"));
    if (fontId < 0) {
        rt_kprintf("QUICK_GALLERY_FONT_FAIL\n");
    } else {
        const QStringList families = QFontDatabase::applicationFontFamilies(fontId);
        if (!families.isEmpty()) {
            app.setFont(QFont(families.constFirst()));
            rt_kprintf("QUICK_GALLERY_FONT %s\n", qPrintable(families.constFirst()));
        }
    }
    QIcon::setThemeName(QStringLiteral("gallery"));

    rt_kprintf("QUICK_GALLERY_STAGE engine\n");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("availableStyles"),
                                             QQuickStyle::availableStyles());
    engine.load(QUrl(QStringLiteral("qrc:/gallery.qml")));
    if (engine.rootObjects().isEmpty()) {
        rt_kprintf("QUICK_GALLERY_FAIL\n");
        return;
    }

    rt_kprintf("QUICK_GALLERY_STAGE visible\n");
    const int result = app.exec();
    rt_kprintf("QUICK_GALLERY_EXIT %d\n", result);
}
