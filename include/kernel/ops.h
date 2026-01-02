
#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include <kernel/types.h>

#define BIT(x) ((uint64)1 << (x))
#define MASK(offset, width) ((BIT(width) - 1) << offset)

static inline uint8 read8(uint64 addr)
{
	volatile uint8 *ptr = (uint8 *)addr;

	return *ptr;
}

static inline uint64 read64(uint64 addr)
{
	volatile uint64 *ptr = (uint64 *)addr;

	return *ptr;
}

static inline void write8(uint64 addr, uint8 value)
{
	volatile uint8 *ptr = (uint8 *)addr;

	*ptr = value;
}

static inline void write64(uint64 addr, uint64 value)
{
	volatile uint64 *ptr = (uint64 *)addr;

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

static inline uint64 deposit(uint64 orig, uint64 shift, uint8 width, uint64 value)
{
	if (shift >= 64) {
		return orig;
	}

	/* remove extra bits from value */
	value &= MASK(0, width);
	value <<= shift;

	/* clear bits that will be rewritten from orig */
	orig &= ~MASK(0, width);

	return orig | value;
}

#endif /* KERNEL_OPS_H */

