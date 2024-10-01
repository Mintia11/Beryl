#ifndef BERYL_KE_DBG_H
#define BERYL_KE_DBG_H

#include <main.h>

void
DbgPrintChar(In char c);

void
DbgPrintString(In const char *string);

void
DbgPrintf(In const char *fmt, ...);

#endif