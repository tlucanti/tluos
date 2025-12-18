
#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include <kernel/types.h>

#define BIT(x) ((uint64)1 << (x))

static inline uint8 read8(uint64 addr)
{
	volatile uint8 *ptr = (uint8 *)addr;

	return *ptr;
}

static inline void write8(uint64 addr, uint8 value)
{
	volatile uint8 *ptr = (uint8 *)addr;

	*ptr = value;
}

static inline uint64 extract(uint64 value, uint64 mask, uint8 offset)
{
	uint64 masked;

	if (offset >= 64) {
		return 0;
	}

	masked = value & mask;
	return masked >> offset;
}

static inline uint64 deposit(uint64 orig, uint64 mask, uint8 offset, uint64 value)
{
	if (offset >= 64) {
		return orig;
	}

	value <<= offset;
	value &= mask;

	/* clear bits that will be rewritten from orig */
	orig &= ~mask;

	return orig | value;
}

#endif /* KERNEL_OPS_H */

