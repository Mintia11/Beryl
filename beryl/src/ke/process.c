#include <beryl.h>
#include <ke.h>
#include <rtl.h>

void
KeInitializeProcess(KeProcess *process, const char *name)
{
    RtlCopyString(process->Name, name, sizeof(process->Name));
    RtlInizializeListHead(&process->ThreadListHead);
}