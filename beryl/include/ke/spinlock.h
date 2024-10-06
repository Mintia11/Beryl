#ifndef BERYL_KE_SPINLOCK_H
#define BERYL_KE_SPINLOCK_H

#include <ke/ipl.h>
#include <main.h>

typedef struct
{
    bool Locked;
} KeSpinlock;

#define KeInitializeSpinlock(spinlock) ((spinlock)->Locked = false)
void
KeAcquireSpinlock(KeSpinlock *spinlock, KiIpl *oldIPL);
void
KeReleaseSpinlock(KeSpinlock *spinlock, KiIpl oldIPL);

#endif