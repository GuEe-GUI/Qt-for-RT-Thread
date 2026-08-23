#include <QGuiApplication>
#include <QQmlError>
#include <QQuickView>
#include <QtPlugin>
#include <QUrl>

#include <rtthread.h>

#include <stdlib.h>

Q_IMPORT_PLUGIN(QRTThreadFbIntegrationPlugin)
Q_IMPORT_PLUGIN(QtQuick2Plugin)
Q_IMPORT_PLUGIN(QEvdevMousePlugin)
Q_IMPORT_PLUGIN(QEvdevKeyboardPlugin)

static void initResources()
{
    Q_INIT_RESOURCE(tvtennis);
}

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);
    initResources();

    putenv(const_cast<char *>("QV4_FORCE_INTERPRETER=1"));
    putenv(const_cast<char *>("QT_QUICK_BACKEND=software"));
    putenv(const_cast<char *>("QSG_RENDER_LOOP=basic"));
    putenv(const_cast<char *>("QT_QPA_PLATFORM=rtthreadfb"));

    int argc = 1;
    char applicationName[] = "quick-tvtennis";
    char *argv[] = { applicationName, nullptr };

    rt_kprintf("QUICK_TVTENNIS_STAGE app\n");
    QGuiApplication app(argc, argv);

    rt_kprintf("QUICK_TVTENNIS_STAGE view\n");
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(QStringLiteral("qrc:/qt-rtthread/tvtennis.qml")));

    if (view.status() == QQuickView::Error) {
        const QList<QQmlError> errors = view.errors();
        for (const QQmlError &error : errors)
            rt_kprintf("QUICK_TVTENNIS_QML_ERROR %s\n", qPrintable(error.toString()));
        rt_kprintf("QUICK_TVTENNIS_FAIL\n");
        return;
    }

    rt_kprintf("QUICK_TVTENNIS_STAGE qml_ready\n");
    view.show();
    rt_kprintf("QUICK_TVTENNIS_STAGE visible\n");

    const int result = app.exec();
    rt_kprintf("QUICK_TVTENNIS_EXIT %d\n", result);
}
