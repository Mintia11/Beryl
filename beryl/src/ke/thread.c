#include <beryl.h>
#include <ke.h>
#include <rtl.h>

void
KeInitializeThread(
    KeProcess *process,
    KeThread *thread,
    const char *name,
    void *kernel_stack,
    size_t kernel_stack_size,
    KeThreadStartRoutine start_routine,
    void *context1,
    void *context2)
{
    RtlCopyString(thread->Name, name, sizeof(thread->Name));

    thread->Process = process;

    KiInitializeContext(
        thread, kernel_stack + kernel_stack_size, start_routine, context1,
        context2);
    thread->KernelStackTop = kernel_stack + kernel_stack_size;

    RtlInsertTailList(&process->ThreadListHead, &thread->ProcessListEntry);
}