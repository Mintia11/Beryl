#include <beryl.h>
#include <ke.h>

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
_putchar(char c) ALIAS(DbgPrintChar);