#ifndef BERYL_KE_INTERRUPTS_H
#define BERYL_KE_INTERRUPTS_H

#include <main.h>

ALWAYS_INLINE void
KeWaitForNextInterrupt();

bool
KeDisableInterrupts();
void
KeEnableInterrupts();

#endif