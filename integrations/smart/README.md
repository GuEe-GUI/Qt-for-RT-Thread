# RT-Smart user-app integration

This directory is the boundary for the future RT-Smart user-space package. It
must use the normal POSIX, pthread and userspace virtual-memory backends. Do not
reuse the kernel launcher, native RT-Thread IPC adaptation, or QV4 high-kernel-
address patch.

The downstream RT-Smart userapps entry should pin a release of this repository,
apply these patch lists in order, and point its cross-build at the RT-Smart SDK:

```text
patches/5.12.12/common/series
patches/5.12.12/smart/series
```

The Smart integration will gain its build entry and launcher after the first
userspace QtCore/QtGui smoke build establishes the exact userapps ABI. Keeping
this boundary explicit prevents an unvalidated kernel SConscript from being
presented as RT-Smart support.
