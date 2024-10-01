#include <beryl.h>
#include <ke.h>
#include <printf/printf.h>
#include <ps.h>

PsProcess KiIdleProcess;

NO_RETURN void
KiIdleThread(void *context1, void *context2);

NO_RETURN void
KiSystemStartupInternal(uintptr_t idle_thread_stack)
{
    DbgPrintf("Hello, %s\n", "World!");
    DbgPrintf("Idle thread stack top: 0x%p\n", idle_thread_stack);

    uint64_t *base_request =
        (uint64_t *)KiGetLimineRequest(KI_LIMINE_BASE_REVISION);
    assert2(
        base_request[2] == 0,
        "Boootloader revision 2 is not supported (expected 0 found %d)",
        base_request[2]);

    KeProcess *pcb = &KiIdleProcess.pcb;

    KeInitializeProcess(pcb, "Idle Process");

    KeThread idle_thread;
    KeInitializeThread(
        pcb, &idle_thread, "Idle Thread", (void *)idle_thread_stack - 0x10000,
        0xF000, KiIdleThread, NULL, NULL);

    KiJumpIntoThread(idle_thread.Context);
}

NO_RETURN void
KiIdleThread(void *context1, void *context2)
{
    (void)context1;
    (void)context2;

    DbgPrintf("Hello from the idle thread!\n");

    while (true)
    {
        KeWaitForNextInterrupt();
    }
}