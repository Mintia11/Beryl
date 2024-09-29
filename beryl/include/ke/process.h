#ifndef BERYL_KE_PROCESS_H
#define BERYL_KE_PROCESS_H

#include <main.h>
#include <rtl.h>

typedef struct
{
    char Name[32];
    RtlListEntry ThreadListHead;
} KeProcess;

void
KeInitializeProcess(KeProcess *process, const char *name);

#endif