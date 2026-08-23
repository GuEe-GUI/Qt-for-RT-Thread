extern "C" int rt_kprintf(const char *fmt, ...);

extern int qt_core_customtype_upstream_main(int argc, char **argv);

extern "C" void qt_main(void *parameter)
{
    char application_name[] = "qt-core-customtype";
    char *argv[] = {application_name, nullptr};

    (void)parameter;
    rt_kprintf("QTCORE_CUSTOMTYPE_STAGE begin\n");

    const int result = qt_core_customtype_upstream_main(1, argv);
    rt_kprintf("QTCORE_CUSTOMTYPE_STAGE done result=%d\n", result);
}
