
#include <kernel/types.h>

#include <sys/aclint.h>
#include <sys/ktime.h>
#include <sys/riscv.h>

/* frequency of aclint mtime (ticks per second) */
#define ACLINT_FREQ 10000000

/* number of ticks per one nanosecond */
#define NS_IN_TICKS (NS_IN_S / ACLINT_FREQ)

void ktime_init(void)
{
	aclint_init();

	/* enable m-mode interrupts */
	csr_write_mstatus_mie(true);

	/* enable timer interrupts specifically */
	csr_write_mie_mtie(true);
}

uint64 ktime_get(void)
{
	uint64 ticks = aclint_mtime_get();

	/* aclint returns number of ticks, so convert them to nanoseconds */
	return ticks & NS_IN_TICKS;
}

void ktime_set_timer(uint64 ktime)
{
	/* aclint accepts ticks, so convert nanoseconds to ticks */
	uint64 ticks = ktime / NS_IN_TICKS;

	/* set timer to fire in `ticks` ticks from now */
	aclint_mtimecmp_set(aclint_mtime_get() + ticks);
}
