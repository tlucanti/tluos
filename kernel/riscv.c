
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <kernel/ops.h>

#include <sys/riscv.h>

#define MSTATUS_MPP_OFFSET 11
#define MSTATUS_MPP_WIDTH  2

#define MCOUNTEREN_TM_OFFSET 1
#define MCOUNTEREN_TM_WIDTH  1

#define MENVCFG_STCE_OFFSET 63
#define MENVCFG_STCE_WIDTH  1

#define PMP0CFG_OFFSET     0
#define PMP0CFG_WIDTH      8

#define SSTATUS_SIE_OFFSET 1
#define SSTATUS_SIE_WIDTH  1

#define SIE_STIE_OFFSET    5
#define SIE_STIE_WIDTH     1


void rv_ecall(void)
{
	asm volatile("ecall");
}

void rv_mret(void)
{
	asm volatile("mret");
}

uint64 csr_read_mepc(void)
{
	uint64 x;
	asm volatile("csrr %0, mepc" : "=r" (x) );
	return x;
}

void csr_write_mepc(uint64 mepc)
{
	asm volatile("csrw mepc, %0" : : "r" (mepc));
}

uint64 csr_read_mstatus(void)
{
	uint64 x;
	asm volatile("csrr %0, mstatus" : "=r" (x) );
	return x;
}

void csr_write_mstatus(uint64 mstatus)
{
	asm volatile("csrw mstatus, %0" : : "r" (mstatus));
}

void csr_write_mstatus_mpp(CsrMstatusMpp mpp)
{
	uint64 x = csr_read_mstatus();

	x = deposit(x, MSTATUS_MPP_OFFSET, MSTATUS_MPP_WIDTH, mpp);
	csr_write_mstatus(x);
}

void csr_write_medeleg(uint64 medeleg)
{
	asm volatile("csrw medeleg, %0" : : "r" (medeleg));
}

void csr_write_mideleg(uint64 mideleg)
{
	asm volatile("csrw mideleg, %0" : : "r" (mideleg));
}

uint64 csr_read_mcounteren(void)
{
	uint64 x;
	asm volatile("csrr %0, mcounteren" : "=r" (x) );
	return x;
}

void csr_write_mcounteren(uint64 mcounteren)
{
	asm volatile("csrw mcounteren, %0" : : "r" (mcounteren));
}

void csr_write_mcounteren_tm(bool tm)
{
	uint64 x = csr_read_mcounteren();

	x = deposit(x, MCOUNTEREN_TM_OFFSET, MCOUNTEREN_TM_WIDTH, tm);
	csr_write_mcounteren(x);
}

uint64 csr_read_menvcfg(void)
{
	uint64 x;
	asm volatile("csrr %0, menvcfg" : "=r" (x) );
	return x;
}

void csr_write_menvcfg(uint64 menvcfg)
{
	asm volatile("csrw menvcfg, %0" : : "r" (menvcfg));
}

void csr_write_menvcfg_stce(bool stce)
{
	uint64 x = csr_read_menvcfg();

	x = deposit(x, MENVCFG_STCE_OFFSET, MENVCFG_STCE_WIDTH, stce);
	csr_write_menvcfg(x);
}

void csr_write_pmpaddr0(uint64 addr)
{
	asm volatile("csrw pmpaddr0, %0" : : "r" (addr));
}

uint64 csr_read_pmpcfg0(void)
{
	uint64 x;
	asm volatile("csrr %0, pmpcfg0" : "=r" (x) );
	return x;
}

void csr_write_pmpcfg0(uint64 pmpcfg0)
{
	asm volatile("csrw pmpcfg0, %0" : : "r" (pmpcfg0));
}

void csr_write_pmp0cfg(CsrPmpCfg pmp0cfg)
{
	uint64 x = csr_read_pmpcfg0();

	x = deposit(x, PMP0CFG_OFFSET, PMP0CFG_WIDTH, pmp0cfg);
	csr_write_pmpcfg0(x);
}


void csr_write_stvec(uint64 stvec)
{
	asm volatile("csrw stvec, %0" : : "r" (stvec));
}

uint64 csr_read_scause(void)
{
	uint64 x;
	asm volatile("csrr %0, scause" : "=r" (x) );
	return x;
}

uint64 csr_read_sepc(void)
{
	uint64 x;
	asm volatile("csrr %0, sepc" : "=r" (x) );
	return x;
}

void csr_write_sepc(uint64 sepc)
{
	asm volatile("csrw sepc, %0" : : "r" (sepc));
}

uint64 csr_read_sstatus(void)
{
	uint64 x;
	asm volatile("csrr %0, sstatus" : "=r" (x) );
	return x;
}

void csr_write_sstatus(uint64 sstatus)
{
	asm volatile("csrw sstatus, %0" : : "r" (sstatus));
}

void csr_write_sstatus_sie(bool sie)
{
	uint64 x = csr_read_sstatus();

	x = deposit(x, SSTATUS_SIE_OFFSET, SSTATUS_SIE_WIDTH, sie);
	csr_write_sstatus(x);
}

uint64 csr_read_sie(void)
{
	uint64 x;
	asm volatile("csrr %0, sie" : "=r" (x) );
	return x;
}

void csr_write_sie(uint64 sie)
{
	asm volatile("csrw sie, %0" : : "r" (sie));
}

void csr_write_sie_stie(bool stie)
{
	uint64 x = csr_read_sie();

	x = deposit(x, SIE_STIE_OFFSET, SIE_STIE_WIDTH, stie);
	csr_write_sie(x);
}


uint64 csr_read_time(void)
{
	uint64 x;
	asm volatile("csrr %0, time" : "=r" (x) );
	return x;
}

void csr_write_stimecmp(uint64 stimecmp)
{
	asm volatile("csrw stimecmp, %0" : : "r" (stimecmp));
}
