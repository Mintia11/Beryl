#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>

void
DbgPrintChar(In char c)
{
    ASM("outb %0, $0xe9" : : "a"(c));
}

void
DbgPrintString(In const char *string)
{
    while (*string)
    {
        DbgPrintChar(*string++);
    }
}

void
DbgPrintf(In const char *fmt, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, fmt);

    vsnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    DbgPrintString(buffer);
}