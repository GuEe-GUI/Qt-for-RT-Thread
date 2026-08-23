#include <rtthread.h>

#include <stdlib.h>

#ifndef PKG_QT_RTTHREAD_THREAD_STACK_SIZE
#define PKG_QT_RTTHREAD_THREAD_STACK_SIZE  (8 * 1024 * 1024)
#endif
#ifndef PKG_QT_RTTHREAD_THREAD_PRIORITY
#define PKG_QT_RTTHREAD_THREAD_PRIORITY    25
#endif
#ifndef PKG_QT_RTTHREAD_THREAD_TIMESLICE
#define PKG_QT_RTTHREAD_THREAD_TIMESLICE   10
#endif
#ifndef PKG_QT_RTTHREAD_POINTER_DEVICE
#define PKG_QT_RTTHREAD_POINTER_DEVICE     "/dev/input1"
#endif
#ifndef PKG_QT_RTTHREAD_KEYBOARD_DEVICE
#define PKG_QT_RTTHREAD_KEYBOARD_DEVICE    "/dev/input2"
#endif
#ifndef PKG_QT_RTTHREAD_FONTDIR
#define PKG_QT_RTTHREAD_FONTDIR            "/fonts/"
#endif

extern void qt_main(void *parameter);

static rt_bool_t qt_running = RT_FALSE;

static void qt_thread_entry(void *parameter)
{
    qt_main(parameter);
    qt_running = RT_FALSE;
}

static void qt_set_device_environment(void)
{
    putenv("QT_QPA_PLATFORM=rtthreadfb");
    putenv("QT_QPA_FONTDIR=" PKG_QT_RTTHREAD_FONTDIR);
    putenv("QT_QPA_FB_HIDECURSOR=0");

#if defined(PKG_QT_RTTHREAD_INPUT_GENERIC)
    putenv("QT_QPA_GENERIC_PLUGINS=evdevmouse,evdevkeyboard");
#endif

#if defined(PKG_QT_RTTHREAD_INPUT_TSLIB)
    putenv("QT_QPA_FB_TSLIB=1");
    putenv("TSLIB_TSDEVICE=" PKG_QT_RTTHREAD_POINTER_DEVICE);
    putenv("TSLIB_CONFFILE=/etc/ts.conf");
    putenv("TSLIB_CALIBFILE=/etc/pointercal");
#else
    putenv("QT_QPA_EVDEV_MOUSE_PARAMETERS="
           PKG_QT_RTTHREAD_POINTER_DEVICE ":abs");
#endif

    putenv("QT_QPA_EVDEV_KEYBOARD_PARAMETERS="
           PKG_QT_RTTHREAD_KEYBOARD_DEVICE);
}

int qt_run(void)
{
    rt_thread_t thread;

    if (qt_running)
        return -RT_EBUSY;

#if defined(PKG_QT_RTTHREAD_QML)
    putenv("QV4_FORCE_INTERPRETER=1");
    putenv("QT_QUICK_BACKEND=software");
    putenv("QSG_RENDER_LOOP=basic");
#endif

    qt_set_device_environment();

    thread = rt_thread_create("Qt", qt_thread_entry, RT_NULL,
                              PKG_QT_RTTHREAD_THREAD_STACK_SIZE,
                              PKG_QT_RTTHREAD_THREAD_PRIORITY,
                              PKG_QT_RTTHREAD_THREAD_TIMESLICE);
    if (!thread)
        return -RT_ENOMEM;

    qt_running = RT_TRUE;
    rt_thread_startup(thread);
    return RT_EOK;
}
MSH_CMD_EXPORT(qt_run, run Qt application);
