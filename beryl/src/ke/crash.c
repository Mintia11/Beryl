#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>

NO_RETURN void
KeCrash(const char *message, ...)
{
    char buffer[1024];
    va_list args;

    DbgPrintString("Kernel crash: \n");

    va_start(args, message);

    vsnprintf(buffer, sizeof(buffer), message, args);
    DbgPrintString(buffer);

    va_end(args);

    for (;;)
    {
        KeWaitForNextInterrupt();
    }
}