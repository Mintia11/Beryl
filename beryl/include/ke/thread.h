#ifndef BERYL_KE_THREAD_H
#define BERYL_KE_THREAD_H

#include <beryl.h>
#include <ke/process.h>
#include <rtl/list.h>

typedef NO_RETURN void (*KeThreadStartRoutine)(void *context1, void *context2);

typedef struct
{
    char Name[32];
    RtlListEntry ProcessListEntry;
    KeProcess *Process;
    void *KernelStackTop;
    OSContext *Context;
} KeThread;

void
KeInitializeThread(
    KeProcess *process,
    KeThread *thread,
    const char *name,
    void *kernel_stack,
    size_t kernel_stack_size,
    KeThreadStartRoutine start_routine,
    void *context1,
    void *context2);

void
KiInitializeContext(
    KeThread *thread,
    void *stack,
    KeThreadStartRoutine start_routine,
    void *context1,
    void *context2);

extern NO_RETURN void
KiJumpIntoThread(OSContext *context);

extern NO_RETURN void
KiThreadTrampoline();

#endif