#include <beryl.h>

#define UART0_BASE 0xffff800010000000

void
DbgPrintChar(In char c)
{
    *(volatile uint8_t *)UART0_BASE = c;
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