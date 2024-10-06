#ifndef BERYL_KE_CPU_LOCAL_H
#define BERYL_KE_CPU_LOCAL_H

#include <ke/ipl.h>
#include <ke/thread.h>
#include <main.h>

typedef struct _KiCpuLocal
{
    struct _KiCpuLocal *Self;
    uint64_t Id;

    KiIpl Ipl;

    KeThread IdleThread;
    void *IdleStackBase;
} KiCpuLocal;

#define KiCurrentPrb() (((__seg_gs KiCpuLocal *)0x0)->Self)

void
KiInitPrb(KiCpuLocal *prb, uint64_t id);

void
KiArchSetPrb(KiCpuLocal *prb);

#endif