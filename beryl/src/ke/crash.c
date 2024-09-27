#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>

NO_RETURN void
KeCrash(const char *message, ...)
{
    va_list args;

    printf("Kernel crash: \n");

    va_start(args, message);
    vprintf(message, args);
    va_end(args);

    for (;;)
    {
        KeWaitForNextInterrupt();
    }
}