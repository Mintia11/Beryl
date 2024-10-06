#include <ke.h>
#include <rtl.h>

FORCE_INLINE void
writecr8(uint64_t value)
{
    ASM("mov %0, %%cr8" : : "r"(value));
}

KiIpl
KeRaiseIPL(KiIpl newIPL)
{
    bool restore = KeDisableInterrupts();

    KiIpl oldIPL = KiCurrentPrb()->Ipl;

    if (oldIPL == newIPL)
    {
        if (restore)
        {
            KeEnableInterrupts();
        }

        return oldIPL;
    }

    assert2(newIPL < oldIPL, "Cannot raise IPL from %d to %d", oldIPL, newIPL);

    writecr8(newIPL);
    KiCurrentPrb()->Ipl = newIPL;

    if (restore)
    {
        KeEnableInterrupts();
    }

    return oldIPL;
}

KiIpl
KeRaiseIPLIfNeeded(KiIpl newIPL)
{
    KiIpl oldIPL = KiCurrentPrb()->Ipl;

    if (oldIPL < newIPL)
    {
        return KeRaiseIPL(newIPL);
    }

    return oldIPL;
}

KiIpl
KeLowerIPL(KiIpl newIPL)
{
    bool restore = KeDisableInterrupts();

    KiIpl oldIPL = KiCurrentPrb()->Ipl;

    if (oldIPL == newIPL)
    {
        if (restore)
        {
            KeEnableInterrupts();
        }

        return oldIPL;
    }

    assert2(newIPL > oldIPL, "Cannot lower IPL from %d to %d", oldIPL, newIPL);

    KiCurrentPrb()->Ipl = newIPL;
    writecr8(newIPL);

    if (restore)
    {
        KeEnableInterrupts();
    }

    return oldIPL;
}