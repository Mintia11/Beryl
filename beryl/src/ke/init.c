#include <beryl.h>
#include <printf/printf.h>

NO_RETURN void
KiSystemStartup(void)
{
    printf("Hello, World!\n");

    while (true)
    {
        KeWaitForNextInterrupt();
    }
}