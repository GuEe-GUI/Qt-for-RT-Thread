# tslib 1.23 patch layout

tslib is fetched from the pinned release in `config/tslib-1.23.sources` and is
built as an independent dependency before Qt. Apply `common/series`, followed
by either `kernel/series` or `smart/series`.

The currently validated kernel build uses unmodified tslib 1.23 source, so the
series files are intentionally empty. RT-Thread-specific policy belongs in the
static build configuration and SDK assembly scripts until a source change is
actually required.
