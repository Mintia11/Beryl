#ifndef BERYL_MAIN_H
#define BERYL_MAIN_H

#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NO_RETURN __attribute__((noreturn))
#define ALIAS(a) __attribute__((alias(#a)))
#define USED __attribute__((used))
#define SECTION(s) __attribute__((section(s)))
#define ALWAYS_INLINE __attribute__((always_inline))
#define FORCE_INLINE ALWAYS_INLINE static inline

#define ASM __asm__ volatile

// TODO: Make theese do something
#define In
#define Out
#define InOut

#endif