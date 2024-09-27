#ifndef BERYL_KE_LIMINE_REQUESTS_H
#define BERYL_KE_LIMINE_REQUESTS_H

#include <beryl.h>
#include <limine.h>

typedef enum
{
    LIMINE_BASE_REVISION,
    LIMINE_PAGING_MODE,
} KiLimineRequest;

ALWAYS_INLINE void *
KiGetLimineRequest(In KiLimineRequest req);

#endif