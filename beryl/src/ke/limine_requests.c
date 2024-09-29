#include <beryl.h>
#include <ke.h>
#include <limine.h>

#define LIMINE_REQUEST USED SECTION(".requests") volatile

USED SECTION(
    ".requests_start_marker") static volatile LIMINE_REQUESTS_START_MARKER;
USED SECTION(".requests_end_marker") static volatile LIMINE_REQUESTS_END_MARKER;

LIMINE_REQUEST LIMINE_BASE_REVISION(2);
extern volatile struct limine_paging_mode_request limine_paging_mode;
LIMINE_REQUEST struct limine_stack_size_request limine_stack_size = {
    .id = LIMINE_STACK_SIZE_REQUEST,
    .revision = 0,
    .stack_size = 0x8000,
};

ALWAYS_INLINE void *
KiGetLimineRequest(In KiLimineRequest idx)
{
    switch (idx)
    {
        case 0:
            return (void *)limine_base_revision;
        case 1:
            return (void *)&limine_paging_mode;
        case 2:
            return (void *)&limine_stack_size;
        default:
            assert2(false, "Invalid limine request index: %d", idx);
    }
}

#undef LIMINE_REQUEST