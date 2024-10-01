#include <beryl.h>
#include <ke.h>
#include <mm.h>

void *
MiAllocateFromEarlyHeap(size_t pages)
{
    struct limine_memmap_request *memmap_req =
        (struct limine_memmap_request *)KiGetLimineRequest(KI_LIMINE_MEMMAP);
    struct limine_memmap_response *memmap_resp =
        (struct limine_memmap_response *)memmap_req->response;

    struct limine_memmap_entry **memmap = memmap_resp->entries;

    for (size_t i = 0; i < memmap_resp->entry_count; i++)
    {
        struct limine_memmap_entry *entry = memmap[i];

        if (entry->type != LIMINE_MEMMAP_USABLE)
            continue;
        if (entry->length < pages * 0x10000)
            continue;

        entry->length -= pages * 0x10000;

        void *ret = (void *)entry->base;
        entry->base += pages * 0x10000;

        return ret;
    }
}