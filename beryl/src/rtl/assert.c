#include <beryl.h>
#include <printf/printf.h>
#include <rtl.h>

#ifdef NDEBUG

NO_RETURN void
RtlAssert(
    In const char *expr,
    In const char *file,
    In int line,
    In const char *format,
    ...)
{
    va_list args;

    char buf[256];

    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    KeCrash(
        "Assertion failed: %s\nFile: %s\nLine: %d\n%s\n", expr, file, line,
        buf);
}

#endif