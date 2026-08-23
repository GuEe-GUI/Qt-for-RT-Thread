#include <QCoreApplication>
#include <QDebug>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QScopedPointer>

#include <rtthread.h>

#include <stdlib.h>

static void stopWithResult(const char *result)
{
    rt_kprintf("%s\n", result);
    while (true)
        rt_thread_mdelay(1000);
}

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);

    putenv(const_cast<char *>("QV4_FORCE_INTERPRETER=1"));

    int argc = 1;
    char applicationName[] = "qml-smoke";
    char *argv[] = { applicationName, nullptr };
    rt_kprintf("QML_SMOKE_STAGE app\n");
    QCoreApplication app(argc, argv);
    rt_kprintf("QML_SMOKE_STAGE engine\n");
    QQmlEngine engine;
    rt_kprintf("QML_SMOKE_STAGE component\n");

    static const char qml[] =
        "import QtQml 2.12\n"
        "QtObject {\n"
        "    property int answer: 6 * 7\n"
        "    property string message: 'rt-' + 'thread'\n"
        "    property var values: [1, 2, 3, 4]\n"
        "    property int total: values.reduce(function(a, b) { return a + b; }, 0)\n"
        "}\n";

    QQmlComponent component(&engine);
    component.setData(qml, QUrl(QStringLiteral("qrc:/qml-smoke.qml")));
    if (component.isError()) {
        qCritical() << "QML_SMOKE_COMPONENT_ERROR" << component.errors();
        stopWithResult("QML_SMOKE_COMPONENT_ERROR");
    }

    rt_kprintf("QML_SMOKE_STAGE create\n");
    QScopedPointer<QObject> root(component.create());
    if (!root) {
        qCritical() << "QML_SMOKE_CREATE_ERROR" << component.errors();
        stopWithResult("QML_SMOKE_CREATE_ERROR");
    }

    const bool propertiesOk = root->property("answer").toInt() == 42
            && root->property("message").toString() == QStringLiteral("rt-thread")
            && root->property("total").toInt() == 10;
    if (!propertiesOk) {
        qCritical() << "QML_SMOKE_PROPERTY_ERROR"
                    << root->property("answer")
                    << root->property("message")
                    << root->property("total");
        stopWithResult("QML_SMOKE_PROPERTY_ERROR");
    }

    rt_kprintf("QML_SMOKE_STAGE allocation\n");
    for (int i = 0; i < 256; ++i) {
        QScopedPointer<QObject> object(component.create());
        if (!object || object->property("answer").toInt() != 42) {
            qCritical() << "QML_SMOKE_ALLOCATION_ERROR" << i << component.errors();
            stopWithResult("QML_SMOKE_ALLOCATION_ERROR");
        }
        if ((i & 31) == 31)
            engine.collectGarbage();
    }

    engine.collectGarbage();
    qInfo() << "QML_SMOKE_PASS" << root.data();
    stopWithResult("QML_SMOKE_PASS");
}
