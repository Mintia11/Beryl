#include <beryl.h>
#include <limine.h>
#include <mm.h>

#define LIMINE_REQUEST USED SECTION(".requests") volatile

LIMINE_REQUEST struct limine_paging_mode_request limine_paging_mode = {
    .id = LIMINE_PAGING_MODE_REQUEST,
    .revision = 1,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL,
    .min_mode = LIMINE_PAGING_MODE_X86_64_4LVL,
    .max_mode = LIMINE_PAGING_MODE_X86_64_4LVL,
};

#undef LIMINE_REQUEST