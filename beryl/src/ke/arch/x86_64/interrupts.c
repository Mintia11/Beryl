#include <beryl.h>
#include <ke.h>

ALWAYS_INLINE void
KeWaitForNextInterrupt()
{
    ASM("hlt");
}