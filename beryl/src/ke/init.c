#include <beryl.h>
#include <ke.h>
#include <mm.h>
#include <printf/printf.h>
#include <ps.h>

PsProcess KiIdleProcess;

NO_RETURN void
KiIdleThread(void *context1, void *context2);

void
KiInitPrb(KiCpuLocal *prb, uint64_t id)
{
    prb->Self = prb;
    prb->Id = id;
    prb->Ipl = KI_IPL_HIGH;

    void *idle_stack = MiAllocateFromEarlyHeap(1);
    prb->IdleStackBase = idle_stack;

    KeProcess *pcb = &KiIdleProcess.pcb;
    KeThread *idle_thread = &prb->IdleThread;

    KeInitializeThread(
        pcb, idle_thread, "Idle Thread", prb->IdleStackBase, 0x1000,
        KiIdleThread, NULL, NULL);
}

NO_RETURN void
KiSystemStartup()
{
    DbgPrintf("Hello, %s\n", "World!");

    uint64_t *base_request =
        (uint64_t *)KiGetLimineRequest(KI_LIMINE_BASE_REVISION);
    assert2(
        base_request[2] == 0,
        "Boootloader revision 2 is not supported (expected 0 found %d)",
        base_request[2]);

    DbgPrintf("Initializing the idle process\n");

    KeProcess *pcb = &KiIdleProcess.pcb;

    KeInitializeProcess(pcb, "Idle Process");

    DbgPrintf("Initializing the core locals\n");

    struct limine_smp_request *smp_request =
        (struct limine_smp_request *)KiGetLimineRequest(KI_LIMINE_SMP);
    uint64_t core_count = smp_request->response->cpu_count;

    KiCpuLocal *prbs = MiAllocateFromEarlyHeap(
        ((core_count * sizeof(KiCpuLocal)) / 0x1000) + 1);

    // Set the first PRB for the BSP so that locking can work
    KiArchSetPrb(&prbs[0]);

    for (uint64_t i = 0; i < core_count; i++)
    {
        KiInitPrb(&prbs[i], i);
    }

    KiJumpIntoThread(KiCurrentPrb()->IdleThread.Context);
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