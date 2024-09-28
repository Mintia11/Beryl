#ifndef BERYL_RTL_ASSERT_H
#define BERYL_RTL_ASSERT_H

#include <main.h>

#ifdef NDEBUG

NO_RETURN void
RtlAssert(In const char *expr, In const char *file, In int line, In const char *format, ...);

#define assert(expr)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
            RtlAssert(#expr, __FILE__, __LINE__, #expr);                                                               \
    } while (0)

#define assert2(expr, format, ...)                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
            RtlAssert(#expr, __FILE__, __LINE__, format __VA_OPT__(, ) __VA_ARGS__);                                   \
    } while (0)

#else
#define assert(expr, ...) (void)(expr)
#define assert2(expr, format, ...) (void)(expr)
#endif

#endif