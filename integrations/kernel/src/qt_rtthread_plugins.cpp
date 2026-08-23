#include <rtconfig.h>
#include <QtPlugin>

Q_IMPORT_PLUGIN(QRTThreadFbIntegrationPlugin)

#if defined(PKG_QT_RTTHREAD_INPUT_GENERIC)
Q_IMPORT_PLUGIN(QEvdevMousePlugin)
Q_IMPORT_PLUGIN(QEvdevKeyboardPlugin)
#endif

#if defined(PKG_QT_RTTHREAD_IMAGEFORMATS)
Q_IMPORT_PLUGIN(QGifPlugin)
Q_IMPORT_PLUGIN(QICOPlugin)
Q_IMPORT_PLUGIN(QJpegPlugin)
#endif

#if defined(PKG_QT_RTTHREAD_QML)
Q_IMPORT_PLUGIN(QtQuick2Plugin)
Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)
Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
#endif

#if defined(PKG_QT_RTTHREAD_QUICK_CONTROLS2)
Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
#endif

#if defined(PKG_QT_RTTHREAD_GALLERY_DEMO)
Q_IMPORT_PLUGIN(QtQuickControls2FusionStylePlugin)
Q_IMPORT_PLUGIN(QtQuickControls2MaterialStylePlugin)
Q_IMPORT_PLUGIN(QtQuickControls2UniversalStylePlugin)
Q_IMPORT_PLUGIN(QmlSettingsPlugin)
#elif defined(PKG_QT_RTTHREAD_STYLE_FUSION)
Q_IMPORT_PLUGIN(QtQuickControls2FusionStylePlugin)
#elif defined(PKG_QT_RTTHREAD_STYLE_MATERIAL)
Q_IMPORT_PLUGIN(QtQuickControls2MaterialStylePlugin)
#elif defined(PKG_QT_RTTHREAD_STYLE_UNIVERSAL)
Q_IMPORT_PLUGIN(QtQuickControls2UniversalStylePlugin)
#endif
