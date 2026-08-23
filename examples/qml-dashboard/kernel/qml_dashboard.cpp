/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-07     GuEe-GUI     the first version
 */

#include <QDebug>
#include <QtPlugin>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

#ifndef QT_RTTHREAD_PACKAGE_MANAGED_PLUGINS
Q_IMPORT_PLUGIN(QRTThreadFbIntegrationPlugin)
Q_IMPORT_PLUGIN(QEvdevMousePlugin)
Q_IMPORT_PLUGIN(QEvdevKeyboardPlugin)
#endif

static int qt_main_cpp(void)
{
    int id, argc = 1;
    char *argv[] =
    {
        (char *)__func__,
    };
    QGuiApplication app(argc, argv);

    id = QFontDatabase::addApplicationFont("/fonts/wqy-microhei.ttc");

    if (id >= 0)
    {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QGuiApplication::setFont(QFont(family));

        qDebug() << "Loaded font families:" << QFontDatabase::applicationFontFamilies(id);
    }
    else
    {
        qWarning() << "Failed to load application font.";
    }

    Q_INIT_RESOURCE(qml_dashboard);

    QQmlApplicationEngine engine;

    engine.load(QUrl("qrc:/qml_main.qml"));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);
    qt_main_cpp();
}
