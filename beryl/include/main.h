#ifndef BERYL_MAIN_H
#define BERYL_MAIN_H

#define NO_RETURN __attribute__((noreturn))
#define ALIAS(a) __attribute__((alias(a)))
#define ALWAYS_INLINE __attribute__((always_inline))
#define FORCE_INLINE ALWAYS_INLINE static inline

#define ASM __asm__ volatile

// TODO: Make theese do something
#define In
#define Out
#define InOut

#endif