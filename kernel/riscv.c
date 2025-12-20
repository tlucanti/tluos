
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <kernel/ops.h>

#include <sys/riscv.h>

#define MSTATUS_MIE_OFFSET 3
#define MSTATUS_MIE_MASK   BIT(3)

#define MIE_MTIE_OFFSET    7
#define MIE_MTIE_MASK      BIT(7)

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

uint64 csr_read_mcause(void)
{
	uint64 x;
	asm volatile("csrr %0, mcause" : "=r" (x) );
	return x;
}

uint64 csr_read_mstatus(void)
{
	uint64 x;
	asm volatile("csrr %0, mstatus" : "=r" (x) );
	return x;
}

void csr_write_mstatus(uint64 x)
{
	asm volatile("csrw mstatus, %0" : : "r" (x));
}

void csr_write_mstatus_mie(bool enable)
{
	uint64 x = csr_read_mstatus();

	x = deposit(x, MSTATUS_MIE_MASK, MSTATUS_MIE_OFFSET, enable);
	csr_write_mstatus(x);
}

uint64 csr_read_mie(void)
{
	uint64 x;
	asm volatile("csrr %0, mie" : "=r" (x) );
	return x;
}

void csr_write_mie(uint64 x)
{
	asm volatile("csrw mie, %0" : : "r" (x));
}

void csr_write_mie_mtie(bool enable)
{
	uint64 x = csr_read_mie();

	x = deposit(x, MIE_MTIE_MASK, MIE_MTIE_OFFSET, enable);
	csr_write_mie(x);
}

