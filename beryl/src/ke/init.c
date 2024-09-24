#include <beryl.h>
#include <printf/printf.h>

NO_RETURN void
KiSystemStartup(void)
{
    printf("Hello, %s\n", "World!");

    while (true)
    {
        KeWaitForNextInterrupt();
    }
}