
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/riscv.h>

struct mstatus {
	union {
		uint64 value;
		struct {
			uint64 uie  : 1;
			uint64 sie  : 1;
			uint64      : 1;
			uint64 mie  : 1;
			uint64 upie : 1;
			uint64 spie : 1;
			uint64      : 1;
			uint64 mpie : 1;
			uint64 spp  : 1;
			uint64      : 2;
			uint64 mpp  : 2;
			uint64 fs   : 2;
			uint64 xs   : 2;
			uint64 mprv : 1;
			uint64 sum  : 1;
			uint64 mxr  : 1;
			uint64 tvm  : 1;
			uint64 tw   : 1;
			uint64 tsr  : 1;
			uint64      : 9;
			uint64 uxl  : 2;
			uint64 sxl  : 2;
			uint64      : 27;
			uint64 sd   : 1;
		};
	};
};

/**
 * RISC-V instructions mapping
 */

__always_inline
void rv_ecall(void)
{
	asm volatile("ecall");
}

__always_inline
void rv_wfi(void)
{
	asm volatile("wfi");
}

__always_inline __noreturn
void rv_mret(void)
{
	asm volatile("mret");
	unreachable();
}

/**
 * Machine mode registers
 */

/* machine information registers */

__always_inline
uint64 csr_read_mvendorid(void)
{
	uint64 x;
	asm volatile("csrr %0, mvendorid" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_marchid(void)
{
	uint64 x;
	asm volatile("csrr %0, marchid" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mimpid(void)
{
	uint64 x;
	asm volatile("csrr %0, mimpid" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mhartid(void)
{
	uint64 x;
	asm volatile("csrr %0, mhartid" : "=r" (x) );
	return x;
}

/* machine trap setup */

__always_inline
uint64 csr_read_mstatus(void)
{
	uint64 x;
	asm volatile("csrr %0, mstatus" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_misa(void)
{
	uint64 x;
	asm volatile("csrr %0, misa" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mie(void)
{
	uint64 x;
	asm volatile("csrr %0, mie" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mcounteren(void)
{
	uint64 x;
	asm volatile("csrr %0, mcounteren" : "=r" (x) );
	return x;
}


__always_inline
void csr_write_medeleg(uint64 x)
{
	asm volatile("csrw medeleg, %0" : : "r" (x));
}

__always_inline
void csr_write_mideleg(uint64 x)
{
	asm volatile("csrw mideleg, %0" : : "r" (x));
}

__always_inline
void csr_write_mstatus(uint64 x)
{
	asm volatile("csrw mstatus, %0" : : "r" (x));
}

__always_inline
void csr_write_mstatus_mpp(enum mstatus_mpp_mode mode)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mpp = mode;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_mpie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mpie = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mie(uint64 x)
{
	asm volatile("csrw mie, %0" : : "r" (x));
}

__always_inline
void csr_write_mtvec(uint64 x)
{
	asm volatile("csrw mtvec, %0" : : "r" (x));
}

__always_inline
void csr_write_mcounteren(uint64 x)
{
	asm volatile("csrw mcounteren, %0" : : "r" (x));
}

/* machine trap handling */

__always_inline
uint64 csr_read_mscratch(void)
{
	uint64 x;
	asm volatile("csrr %0, mscratch" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mepc(void)
{
	uint64 x;
	asm volatile("csrr %0, mepc" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mcause(void)
{
	uint64 x;
	asm volatile("csrr %0, mcause" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mtval(void)
{
	uint64 x;
	asm volatile("csrr %0, mtval" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_mip(void)
{
	uint64 x;
	asm volatile("csrr %0, mip" : "=r" (x) );
	return x;
}


__always_inline
void csr_write_mscratch(uint64 x)
{
	asm volatile("csrw mscratch, %0" : : "r" (x));
}

__always_inline
void csr_write_mepc(uint64 x)
{
	asm volatile("csrw mepc, %0" : : "r" (x));
}

/* machine protection and translation */

__always_inline
void csr_write_pmpcfg0(uint64 x)
{
	asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

/* machine counter/timers */

__always_inline
uint64 csr_read_mcycle(void)
{
	uint64 x;
	asm volatile("csrr %0, mcycle" : "=r" (x) );
	return x;
}

/**
 * Supervisor mode registers
 */

/* supervisor trap setup */

__always_inline
uint64 csr_read_sstatus(void)
{
	uint64 x;
	asm volatile("csrr %0, sstatus" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_sie(void)
{
	uint64 x;
	asm volatile("csrr %0, sie" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_scounteren(void)
{
	uint64 x;
	asm volatile("csrr %0, scounteren" : "=r" (x) );
	return x;
}


__always_inline
void csr_write_sedeleg(uint64 x)
{
	asm volatile("csrw sedeleg, %0" : : "r" (x));
}

__always_inline
void csr_write_sideleg(uint64 x)
{
	asm volatile("csrw sideleg, %0" : : "r" (x));
}

__always_inline
void csr_write_sie(uint64 x)
{
	asm volatile("csrw sie, %0" : : "r" (x));
}

__always_inline
void csr_write_stvec(uint64 x)
{
	asm volatile("csrw stvec, %0" : : "r" (x));
}

__always_inline
void csr_write_scounteren(uint64 x)
{
	asm volatile("csrw scounteren, %0" : : "r" (x));
}

/* supervisor trap handling */

__always_inline
uint64 csr_read_sscratch(void)
{
	uint64 x;
	asm volatile("csrr %0, sscratch" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_sepc(void)
{
	uint64 x;
	asm volatile("csrr %0, sepc" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_scause(void)
{
	uint64 x;
	asm volatile("csrr %0, scause" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_stval(void)
{
	uint64 x;
	asm volatile("csrr %0, stval" : "=r" (x) );
	return x;
}

__always_inline
uint64 csr_read_sip(void)
{
	uint64 x;
	asm volatile("csrr %0, sip" : "=r" (x) );
	return x;
}

__always_inline
void csr_write_sscratch(uint64 x)
{
	asm volatile("csrw sscratch, %0" : : "r" (x));
}

__always_inline
void csr_write_sepc(uint64 x)
{
	asm volatile("csrw sepc, %0" : : "r" (x));
}

/* supervisor protection and translation */

__always_inline
uint64 csr_read_satp(void)
{
	uint64 x;
	asm volatile("csrr %0, satp" : "=r" (x) );
	return x;
}

__always_inline
void csr_write_satp(uint64 x)
{
	asm volatile("csrw satp, %0" : : "r" (x));
}

