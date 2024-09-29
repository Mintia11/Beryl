#ifndef BERYL_RTL_LIST_H
#define BERYL_RTL_LIST_H

#include <main.h>

typedef struct _RtlListEntry
{
    struct _RtlListEntry *Flink;
    struct _RtlListEntry *Blink;
} RtlListEntry;

#define RtlInizializeListHead(ListHead)                                        \
    (ListHead)->Flink = (ListHead)->Blink = (ListHead)
#define RtlInsertHeadList(ListHead, Entry)                                     \
    (Entry)->Flink = (ListHead)->Flink;                                        \
    (Entry)->Blink = (ListHead);                                               \
    (ListHead)->Flink->Blink = (Entry);                                        \
    (ListHead)->Flink = (Entry)
#define RtlInsertTailList(ListHead, Entry)                                     \
    (Entry)->Flink = (ListHead);                                               \
    (Entry)->Blink = (ListHead)->Blink;                                        \
    (ListHead)->Blink->Flink = (Entry);                                        \
    (ListHead)->Blink = (Entry)
#define RtlIsListEmpty(ListHead) ((ListHead)->Flink == (ListHead))

FORCE_INLINE RtlListEntry *
RtlRemoveHeadList(RtlListEntry *ListHead)
{
    RtlListEntry *Flink;
    RtlListEntry *Entry;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;

    return Entry;
}

FORCE_INLINE RtlListEntry *
RtlRemoveTailList(RtlListEntry *ListHead)
{
    RtlListEntry *Blink;
    RtlListEntry *Entry;

    Entry = ListHead->Blink;
    Blink = Entry->Blink;
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;

    return Entry;
}

FORCE_INLINE RtlListEntry *
RtlRemoveEntryList(RtlListEntry *Entry)
{
    RtlListEntry *Flink;
    RtlListEntry *Blink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;

    return Entry;
}

#endif