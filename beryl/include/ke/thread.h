#ifndef BERYL_KE_THREAD_H
#define BERYL_KE_THREAD_H

#include <ke/process.h>
#include <main.h>
#include <rtl/list.h>

typedef struct _KeThreadContext KeThreadContext;

typedef NO_RETURN void (*KeThreadStartRoutine)(void *context1, void *context2);

typedef struct
{
    char Name[32];
    RtlListEntry ProcessListEntry;
    KeProcess *Process;
    void *KernelStackTop;
    KeThreadContext *Context;
} KeThread;

#if __x86_64__
typedef struct _KeThreadContext
{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t rbx;
    uint64_t rbp;

    uint64_t rip;
} KeThreadContext;
#else
#error "Unsupported architecture"
#endif

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
KiJumpIntoThread(KeThreadContext *context);

extern NO_RETURN void
KiThreadTrampoline();

#endif