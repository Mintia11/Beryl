#include <beryl.h>
#include <ke.h>

void
KiInitializeContext(
    KeThread *thread,
    void *stack,
    KeThreadStartRoutine start_routine,
    void *context1,
    void *context2)
{
    OSContext *context = (OSContext *)stack - 1;

    context->rip = (uint64_t)KiThreadTrampoline;
    context->rbx = (uint64_t)start_routine;
    context->r12 = (uint64_t)context1;
    context->r13 = (uint64_t)context2;

    thread->Context = context;
}