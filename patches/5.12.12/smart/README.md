# RT-Smart user-space patches

This series targets ELF applications running as RT-Smart user processes. It
uses the POSIX/pthread Qt backends and must not depend directly on RT-Thread
kernel IPC objects.

Apply the files listed in `series` after `../common/series`. The empty initial
series intentionally records that RT-Smart support has not yet borrowed any
kernel-only patches.
