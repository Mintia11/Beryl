#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>

NO_RETURN void
KiSystemStartup(void)
{
    printf("Hello, %s\n", "World!");

    uint64_t *base_request = (uint64_t *)KiGetLimineRequest(LIMINE_BASE_REVISION);
    assert2(base_request[2] == 0, "Boootloader revision 2 is not supported (expected 0 found %d)", base_request[2]);

    while (true)
    {
        KeWaitForNextInterrupt();
    }
}