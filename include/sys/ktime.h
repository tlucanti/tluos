
#ifndef SYS_KTIME_H
#define SYS_KTIME_H

#include <kernel/types.h>

/* number of nanoseconds per second */
#define NS_IN_S (uint64)1000000000

void ktime_init(void);
uint64 ktime_get(void);
void ktime_set_timer(uint64 ktime);

static inline uint64 KTIME_TO_S(uint64 ktime)
{
	return ktime / NS_IN_S;
}

static inline uint64 KTIME_TO_NS(uint64 ktime)
{
	return ktime % NS_IN_S;
}

#endif /* SYS_KTIME_H */


