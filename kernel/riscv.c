
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <kernel/panic.h>

#include <sys/riscv.h>

#define SATP_PPN_MAX (BIT(44) - 1)

#define MSTATUS_MPP_OFFSET 11
#define MSTATUS_MPP_WIDTH  2

#define PMP0CFG_OFFSET     0
#define PMP0CFG_WIDTH      8

#define MCOUNTEREN_TM_OFFSET 1
#define MCOUNTEREN_TM_WIDTH  1

#define MENVCFG_STCE_OFFSET 63
#define MENVCFG_STCE_WIDTH  1

#define SSTATUS_SIE_OFFSET 1
#define SSTATUS_SIE_WIDTH  1

#define SIE_STIE_OFFSET    5
#define SIE_STIE_WIDTH     1

#define SATP_ASID_OFFSET   44
#define SATP_ASID_WIDTH    16

#define SATP_MODE_OFFSET   60
#define SATP_MODE_WIDTH    4

// riscv instructions mappings

void rv_ecall(void)
{
	asm volatile("ecall");
}

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

void csr_write_medeleg(uint64 medeleg)
{
	asm volatile("csrw medeleg, %0" : : "r" (medeleg));
}

void csr_write_mideleg(uint64 mideleg)
{
	asm volatile("csrw mideleg, %0" : : "r" (mideleg));
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

uint64 csr_read_mcounteren(void)
{
	uint64 mcounteren;
	asm volatile("csrr %0, mcounteren" : "=r" (mcounteren) );
	return mcounteren;
}

void csr_write_mcounteren(uint64 mcounteren)
{
	asm volatile("csrw mcounteren, %0" : : "r" (mcounteren));
}

void csr_write_mcounteren_tm(bool tm)
{
	uint64 mcounteren = csr_read_mcounteren();

	mcounteren = deposit(mcounteren, MCOUNTEREN_TM_OFFSET, MCOUNTEREN_TM_WIDTH, tm);
	csr_write_mcounteren(mcounteren);
}

uint64 csr_read_menvcfg(void)
{
	uint64 menvcfg;
	asm volatile("csrr %0, menvcfg" : "=r" (menvcfg) );
	return menvcfg;
}

void csr_write_menvcfg(uint64 menvcfg)
{
	asm volatile("csrw menvcfg, %0" : : "r" (menvcfg));
}

void csr_write_menvcfg_stce(bool stce)
{
	uint64 menvcfg = csr_read_menvcfg();

	menvcfg = deposit(menvcfg, MENVCFG_STCE_OFFSET, MENVCFG_STCE_WIDTH, stce);
	csr_write_menvcfg(menvcfg);
}

// s-mode csr mapings

void csr_write_stvec(uint64 stvec)
{
	asm volatile("csrw stvec, %0" : : "r" (stvec));
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

uint64 csr_read_scause(void)
{
	uint64 x;
	asm volatile("csrr %0, scause" : "=r" (x) );
	return x;
}

uint64 csr_read_sepc(void)
{
	uint64 sepc;
	asm volatile("csrr %0, sepc" : "=r" (sepc) );
	return sepc;
}

void csr_write_sepc(uint64 sepc)
{
	asm volatile("csrw sepc, %0" : : "r" (sepc));
}

void csr_write_satp(uint64 satp)
{
	asm volatile("csrw satp, %0" : : "r" (satp));
}

void csr_set_satp(CsrSatpMode mode, uint16 asid, uint64 ppn)
{
	uint64 satp = 0;

	if (ppn > SATP_PPN_MAX) {
		panic("satp ppn too large");
	}

	satp |= ppn;
	satp = deposit(satp, SATP_ASID_OFFSET, SATP_ASID_WIDTH, asid);
	satp = deposit(satp, SATP_MODE_OFFSET, SATP_MODE_WIDTH, mode);

	csr_write_satp(satp);
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
