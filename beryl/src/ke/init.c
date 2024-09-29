#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>

KeProcess KiIdleProcess;

NO_RETURN void
KiIdleThread(void *context1, void *context2);

NO_RETURN void
KiSystemStartupInternal(uintptr_t idle_thread_stack)
{
    printf("Hello, %s\n", "World!");
    printf("Idle thread stack top: 0x%p\n", idle_thread_stack);

    uint64_t *base_request =
        (uint64_t *)KiGetLimineRequest(KI_LIMINE_BASE_REVISION);
    assert2(
        base_request[2] == 0,
        "Boootloader revision 2 is not supported (expected 0 found %d)",
        base_request[2]);

    KeInitializeProcess(&KiIdleProcess, "Idle Process");

    KeThread idle_thread;
    KeInitializeThread(
        &KiIdleProcess, &idle_thread, "Idle Thread",
        (void *)idle_thread_stack - 0x10000, 0xF000, KiIdleThread, NULL, NULL);

    KiJumpIntoThread(idle_thread.Context);
}

NO_RETURN void
KiIdleThread(void *context1, void *context2)
{
    printf("Hello from the idle thread!\n");

    while (true)
    {
        KeWaitForNextInterrupt();
    }
}