#include <beryl.h>
#include <ke.h>

ALWAYS_INLINE void
KeWaitForNextInterrupt()
{
    ASM("hlt");
}

bool
KeDisableInterrupts()
{
    bool old;

    ASM("pushfq\n"
        "pop %%rax\n"
        "cli\n"
        : "=a"(old)
        :
        : "memory");

    return old;
}

void
KeEnableInterrupts()
{
    ASM("sti");
}