
#include <kernel/attributes.h>
#include <kernel/types.h>

#define CLINT_BASE	0x2000000

#define CLINT_MSIP	(CLINT_BASE + 0x0)
#define CLINT_MTIMECMP	(CLINT_BASE + 0x4000)
#define CLINT_MTIME	(CLINT_BASE + 0xBFF8)

#define WRITE_REG(addr, val)						\
	do {								\
		*(volatile uint64 *)(addr) = *(volatile uint64 *)(val);	\
	} while (false)

#define READ_REG(addr) ({ *(volatile uint64 *)(addr); })

/**
 * CLINT direct register interface
 */

/* read registers */
__always_inline __maybe_unused
static uint64 reg_read_msip(void)
{
	return READ_REG(CLINT_MSIP);
}

__always_inline __maybe_unused
static uint64 reg_read_mtimecmp(void)
{
	return READ_REG(CLINT_MTIMECMP);
}

__always_inline __maybe_unused
static uint64 reg_read_mtime(void)
{
	return READ_REG(CLINT_MTIME);
}

/* write registers */
__always_inline __maybe_unused
static void reg_write_msip(uint64 val)
{
	WRITE_REG(CLINT_MSIP, &val);
}

__always_inline __maybe_unused
static void reg_write_mtimecmp(uint64 val)
{
	WRITE_REG(CLINT_MTIMECMP, &val);
}

__always_inline __maybe_unused
static void reg_write_mtime(uint64 val)
{
	WRITE_REG(CLINT_MTIME, &val);
}

/**
 * CLINT public interface
 */
uint64 ktime(void)
{
	return reg_read_mtime();
}

void ktimer_set(uint64 time)
{
	reg_write_mtimecmp(time);
}

