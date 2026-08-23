# Build scripts

The scripts in this directory will implement four explicit stages:

1. fetch and verify upstream source archives;
2. apply an ordered target-specific patch series;
3. build host Qt tools;
4. cross-build and assemble a relocatable target SDK.

No script may contain workstation-specific absolute paths.

`assemble_kernel_sdk.py` is the boundary between the expensive Qt cross-build
and normal BSP builds. It copies a completed Qt installation into the layout
consumed by `integrations/kernel/SConscript` and can include any selected demo
archive:

```text
python scripts/assemble_kernel_sdk.py \
    build-gcc7/install \
    qt-rtthread-port/integrations/kernel/sdk/kernel \
    qt-rtthread-port/examples/core-customtype/kernel/build-gcc7/libqt_core_customtype.a
```

The command refuses to overwrite an existing SDK directory. Release automation
should assemble into a fresh staging directory and archive that directory as a
versioned package artifact. It uses only Python's standard library and supports
both Windows and POSIX host paths.
