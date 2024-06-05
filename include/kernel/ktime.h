
#ifndef SYS_CLINT_H
#define SYS_CLINT_H

#include <kernel/types.h>

uint64 ktime(void);
void ktimer_set(uint64 time);

#endif /* SYS_CLINT_H */

