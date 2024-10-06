#include <beryl.h>
#include <ke.h>

void
KeAcquireSpinlock(KeSpinlock *spinlock, KiIpl *oldIPL)
{
    *oldIPL = KeRaiseIPL(KI_IPL_DPC);

    while (true)
    {
        if (!__atomic_test_and_set(&spinlock->Locked, __ATOMIC_ACQUIRE))
            return;

        while (spinlock->Locked)
            ;
    }
}

void
KeReleaseSpinlock(KeSpinlock *spinlock, KiIpl oldIPL)
{
    __atomic_clear(&spinlock->Locked, __ATOMIC_RELEASE);
    KeLowerIPL(oldIPL);
}