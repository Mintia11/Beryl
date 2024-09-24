#ifndef BERYL_KE_ARCH_H
#define BERYL_KE_ARCH_H

#include <main.h>

void
DbgPrintChar(In char c);

void
DbgPrintString(In const char *string);

ALWAYS_INLINE void
KeWaitForNextInterrupt();

#endif