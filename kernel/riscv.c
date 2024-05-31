
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/riscv.h>

#define MSTATUS_MPP_OFFSET 11
#define MSTATUS_MPP_WIDTH  2

#define PMP0CFG_OFFSET     0
#define PMP0CFG_WIDTH      8

// riscv instructions mappings

void rv_mret(void)
{
	asm volatile("mret");
}

// m-mode csr mapings

uint64 csr_read_mstatus(void)
{
	uint64 mstatus;
	asm volatile("csrr %0, mstatus" : "=r" (mstatus) );
	return mstatus;
}

void csr_write_mstatus(uint64 mstatus)
{
	asm volatile("csrw mstatus, %0" : : "r" (mstatus));
}

void csr_write_mstatus_mpp(CsrMstatusMpp mpp)
{
	uint64 mstatus = csr_read_mstatus();

	mstatus = deposit(mstatus, MSTATUS_MPP_OFFSET, MSTATUS_MPP_WIDTH, mpp);
	csr_write_mstatus(mstatus);
}

void csr_write_mepc(uint64 mepc)
{
	asm volatile("csrw mepc, %0" : : "r" (mepc));
}

void csr_write_pmpaddr0(uint64 addr)
{
	asm volatile("csrw pmpaddr0, %0" : : "r" (addr));
}

uint64 csr_read_pmpcfg0(void)
{
	uint64 pmpcfg0;
	asm volatile("csrr %0, pmpcfg0" : "=r" (pmpcfg0) );
	return pmpcfg0;
}

void csr_write_pmpcfg0(uint64 pmpcfg0)
{
	asm volatile("csrw pmpcfg0, %0" : : "r" (pmpcfg0));
}

void csr_write_pmp0cfg(CsrPmpCfg pmp0cfg)
{
	uint64 pmpcfg0 = csr_read_pmpcfg0();

	pmpcfg0 = deposit(pmpcfg0, PMP0CFG_OFFSET, PMP0CFG_WIDTH, pmp0cfg);
	csr_write_pmpcfg0(pmpcfg0);
}
