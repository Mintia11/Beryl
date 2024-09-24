#include <beryl.h>

ALWAYS_INLINE void
KeWaitForNextInterrupt()
{
    ASM("wfi");
}