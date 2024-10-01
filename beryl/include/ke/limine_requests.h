#ifndef BERYL_KE_LIMINE_REQUESTS_H
#define BERYL_KE_LIMINE_REQUESTS_H

#include <limine.h>
#include <main.h>

typedef enum
{
    KI_LIMINE_BASE_REVISION,
    KI_LIMINE_PAGING_MODE,
    KI_LIMINE_STACK_SIZE,
    KI_LIMINE_MEMMAP,
} KiLimineRequest;

ALWAYS_INLINE void *
KiGetLimineRequest(In KiLimineRequest req);

#endif