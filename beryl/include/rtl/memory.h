#ifndef BERYL_RTL_MEMORY_H
#define BERYL_RTL_MEMORY_H

#include <main.h>

void *
memcpy(Out void *dest, In const void *src, In size_t n);
void *
memset(Out void *s, In int c, In size_t n);
void *
memmove(Out void *dest, In const void *src, In size_t n);
int
memcmp(In const void *s1, In const void *s2, In size_t n);

void
RtlCopyString(void *destination, const void *source, size_t len);

#endif