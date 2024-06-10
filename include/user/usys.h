
#ifndef USER_USYS_H
#define USER_USYS_H

#include <kernel/types.h>

uint getcpu(void);
void print(const char *s);
void spawn(void (*task)(void));
void sched(void);

#endif /* USER_SYSCALLS_H */
