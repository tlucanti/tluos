
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/riscv.h>

void rv_ecall(void)
{
	asm volatile("ecall");
}

uint64 csr_read_mepc(void)
{
	uint64 x;
	asm volatile("csrr %0, mepc" : "=r" (x) );
	return x;
}

void csr_write_mepc(uint64 x)
{
	asm volatile("csrw mepc, %0" : : "r" (x));
}

void csr_write_mtvec(uint64 x)
{
	asm volatile("csrw mtvec, %0" : : "r" (x));
}

