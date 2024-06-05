/**
 * RISC-V ACLINT driver
 */

#include <kernel/types.h>
#include <kernel/ops.h>

#include <sys/aclint.h>

#define ACLINT_BASE	0x2004000

#define ACLINT_MTIMECMP	0x0
#define ACLINT_MTIME	0x7ff8

void aclint_init(void)
{
	/*
	 * set interrupt time to max value to prevent firing
	 * right after interrupt enabled
	 */
	aclint_mtimecmp_set(-1);
}

uint64 aclint_mtime_get(void)
{
	return read64(ACLINT_BASE + ACLINT_MTIME);
}

void aclint_mtimecmp_set(uint64 time)
{
	write64(ACLINT_BASE + ACLINT_MTIMECMP, time);
}

