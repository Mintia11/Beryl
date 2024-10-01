#ifndef BERYL_MM_EARLY_HEAP_H
#define BERYL_MM_EARLY_HEAP_H

#include <main.h>
#include <mm.h>

void *
MiAllocateFromEarlyHeap(size_t pages);

#endif