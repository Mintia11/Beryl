#include <beryl.h>
#include <ke.h>
#include <mm.h>

FORCE_INLINE void
wrmsr(uint64_t msr, uint64_t value)
{
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    ASM("wrmsr" : : "c"(msr), "a"(low), "d"(high));
}

void
KiArchSetPrb(KiCpuLocal *prb)
{
    wrmsr(0xC0000101, (uint64_t)prb);
}