#include <rtthread.h>

/*
 * These functions deliberately live in the BSP/package build, rather than
 * QtCore.  That keeps QtCore binary-compatible with RT-Thread kernel and
 * Smart TCB layouts, whose user_data member has a different offset.
 */
rt_ubase_t qt_rtthread_thread_data_get(void)
{
    rt_thread_t thread = rt_thread_self();

    return thread ? thread->user_data : 0;
}

void qt_rtthread_thread_data_set(rt_ubase_t value)
{
    rt_thread_t thread = rt_thread_self();

    if (thread)
        thread->user_data = value;
}
