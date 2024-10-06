#ifndef BERYL_KE_IPL_H
#define BERYL_KE_IPL_H

#include <main.h>

typedef enum
{
    KI_IPL_PASSIVE = 0x0,
    KI_IPL_DPC = 0x3,
    KI_IPL_HIGH = 0xF,
} KiIpl;

KiIpl
KeRaiseIPL(KiIpl newIPL);

KiIpl
KeRaiseIPLIfNeeded(KiIpl newIPL);

KiIpl
KeLowerIPL(KiIpl newIPL);

#endif