
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

struct mie {
	union {
		uint64 value;
		struct {
			uint64 usie : 1;
			uint64 ssie : 1;
			uint64      : 1;
			uint64 msie : 1;
			uint64 utie : 1;
			uint64 stie : 1;
			uint64      : 1;
			uint64 mtie : 1;
			uint64 ueie : 1;
			uint64 seie : 1;
			uint64      : 1;
			uint64 meie : 1;
		};
	};
};

struct pmpcfg0 {
	union {
		uint64 value;
		struct {
			uint8 pmp0cfg;
			uint8 pmp1cfg;
			uint8 pmp2cfg;
			uint8 pmp3cfg;
			uint8 pmp4cfg;
			uint8 pmp5cfg;
			uint8 pmp6cfg;
			uint8 pmp7cfg;
		};
	};
};

struct pmpcfg2 {
	union {
		uint64 value;
		struct {
			uint8 pmp8cfg;
			uint8 pmp9cfg;
			uint8 pmp10cfg;
			uint8 pmp11cfg;
			uint8 pmp12cfg;
			uint8 pmp13cfg;
			uint8 pmp14cfg;
			uint8 pmp15cfg;
		};
	};
};

struct sstatus {
	union {
		uint64 value;
		struct {
			uint64 uie  : 1;
			uint64 sie  : 1;
			uint64      : 2;
			uint64 upie : 1;
			uint64 spie : 1;
			uint64      : 2;
			uint64 spp  : 1;
			uint64      : 4;
			uint64 fs   : 2;
			uint64 xs   : 2;
			uint64      : 1;
			uint64 sum  : 1;
			uint64 mxr  : 1;
			uint64      : 12;
			uint64 uxl  : 2;
			uint64      : 29;
			uint64 sd   : 1;
		};
	};
};

struct sie {
	union {
		uint64 value;
		struct {
			uint64 usie : 1;
			uint64 ssie : 1;
			uint64      : 2;
			uint64 utie : 1;
			uint64 stie : 1;
			uint64      : 2;
			uint64 ueie : 1;
			uint64 seie : 1;
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
bool csr_read_mstatus_uie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.uie;
}

__always_inline
bool csr_read_mstatus_upie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.upie;
}

__always_inline
bool csr_read_mstatus_sie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.sie;
}

__always_inline
bool csr_read_mstatus_spie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.spie;
}

__always_inline
bool csr_read_mstatus_spp(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.spp;
}

__always_inline
bool csr_read_mstatus_sum(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.sum;
}

__always_inline
bool csr_read_mstatus_sd(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.sd;
}

__always_inline
bool csr_read_mstatus_mie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.mie;
}

__always_inline
bool csr_read_mstatus_mpie(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.mpie;
}

__always_inline
enum mstatus_mpp csr_read_mstatus_mpp(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.mpp;
}

__always_inline
bool csr_read_mstatus_mprv(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.mprv;
}

__always_inline
bool csr_read_mstatus_mxr(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.mxr;
}

__always_inline
enum mstatus_fs csr_read_mstatus_fs(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.fs;
}

__always_inline
enum mstatus_xs csr_read_mstatus_xs(void)
{
	struct mstatus mstatus;
	mstatus.value = csr_read_mstatus();
	return mstatus.xs;
}

__always_inline
uint64 csr_read_misa(void)
{
	uint64 x;
	asm volatile("csrr %0, misa" : "=r" (x) );
	return x;
}

__always_inline
struct misa_extensions csr_read_misa_extensions(void)
{
	const uint64 MISA_EXTENSIONS_MASK = (1ul << 27) - 1; // first 26 bits are extension bits
	struct misa_extensions extensions;
	extensions.value = csr_read_misa() & MISA_EXTENSIONS_MASK;
	return extensions;
}

__always_inline
uint64 csr_read_mie(void)
{
	uint64 x;
	asm volatile("csrr %0, mie" : "=r" (x) );
	return x;
}

__always_inline
bool csr_read_mie_usie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.usie;
}

__always_inline
bool csr_read_mie_utie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.utie;
}

__always_inline
bool csr_read_mie_ueie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.ueie;
}

__always_inline
bool csr_read_mie_ssie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.ssie;
}

__always_inline
bool csr_read_mie_stie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.stie;
}

__always_inline
bool csr_read_mie_seie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.seie;
}

__always_inline
bool csr_read_mie_msie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.msie;
}

__always_inline
bool csr_read_mie_mtie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.mtie;
}

__always_inline
bool csr_read_mie_meie(void)
{
	struct mie mie;
	mie.value = csr_read_mie();
	return mie.meie;
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
void csr_write_mstatus_uie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.uie = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_upie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.upie = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_sie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.sie = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_spie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.spie = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_spp(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.spp = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_sum(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.sum = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_sd(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.sd = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_mie(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mie = enable;
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
void csr_write_mstatus_mpp(enum mstatus_mpp mpp)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mpp = mpp;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_mprv(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mprv = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_mxr(bool enable)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.mxr = enable;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_fs(enum mstatus_fs fs)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.fs = fs;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mstatus_xs(enum mstatus_xs xs)
{
	struct mstatus mstatus;

	mstatus.value = csr_read_mstatus();
	mstatus.xs = xs;
	csr_write_mstatus(mstatus.value);
}

__always_inline
void csr_write_mie(uint64 x)
{
	asm volatile("csrw mie, %0" : : "r" (x));
}

__always_inline
void csr_write_mie_usie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.usie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_utie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.utie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_ueie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.ueie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_ssie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.ssie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_stie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.stie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_seie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.seie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_msie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.msie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_mtie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.mtie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mie_meie(bool enable)
{
	struct mie mie;

	mie.value = csr_read_mie();
	mie.meie = enable;
	csr_write_mie(mie.value);
}

__always_inline
void csr_write_mtvec(uint64 x)
{
	asm volatile("csrw mtvec, %0" : : "r" (x));
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

static __always_inline
uint64 csr_read_pmpcfg0(void)
{
	uint64 x;
	asm volatile("csrr %0, pmpcfg0" : "=r" (x) );
	return x;
}

static __always_inline
uint64 csr_read_pmpcfg2(void)
{
	uint64 x;
	asm volatile("csrr %0, pmpcfg2" : "=r" (x) );
	return x;
}

__always_inline
void csr_write_pmpcfg0(uint64 x)
{
	asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

__always_inline
void csr_write_pmpcfg2(uint64 x)
{
	asm volatile("csrw pmpcfg2, %0" : : "r" (x));
}

__always_inline
void csr_write_pmp0cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp0cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp1cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp1cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp2cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp2cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp3cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp3cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp4cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp4cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp5cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp5cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp6cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp6cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp7cfg(uint8 flags)
{
	struct pmpcfg0 pmpcfg0;

	pmpcfg0.value = csr_read_pmpcfg0();
	pmpcfg0.pmp7cfg = flags;
	csr_write_pmpcfg0(pmpcfg0.value);
}

__always_inline
void csr_write_pmp8cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp8cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp9cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp9cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp10cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp10cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp11cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp11cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp12cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp12cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp13cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp13cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp14cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp14cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmp15cfg(uint8 flags)
{
	struct pmpcfg2 pmpcfg2;

	pmpcfg2.value = csr_read_pmpcfg2();
	pmpcfg2.pmp15cfg = flags;
	csr_write_pmpcfg0(pmpcfg2.value);
}

__always_inline
void csr_write_pmpaddr0(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr0, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr1(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr1, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr2(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr2, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr3(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr3, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr4(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr4, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr5(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr5, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr6(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr6, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr7(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr7, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr8(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr8, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr9(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr9, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr10(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr10, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr11(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr11, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr12(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr12, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr13(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr13, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr14(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr14, %0" : : "r" (address));
}

__always_inline
void csr_write_pmpaddr15(uint64 address)
{
	address <<= 2;
	asm volatile("csrw pmpaddr15, %0" : : "r" (address));
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
bool csr_read_sstatus_uie(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.uie;
}

__always_inline
bool csr_read_sstatus_upie(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.upie;
}

__always_inline
bool csr_read_sstatus_sie(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.sie;
}

__always_inline
bool csr_read_sstatus_spie(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.spie;
}

__always_inline
bool csr_read_sstatus_spp(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.spp;
}

__always_inline
bool csr_read_sstatus_sum(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.sum;
}

__always_inline
bool csr_read_sstatus_sd(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.sd;
}

__always_inline
bool csr_read_sstatus_mxr(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.mxr;
}

__always_inline
enum sstatus_fs csr_read_sstatus_fs(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.fs;
}

__always_inline
enum sstatus_xs csr_read_sstatus_xs(void)
{
	struct sstatus sstatus;
	sstatus.value = csr_read_sstatus();
	return sstatus.xs;
}

__always_inline
uint64 csr_read_sie(void)
{
	uint64 x;
	asm volatile("csrr %0, sie" : "=r" (x) );
	return x;
}

__always_inline
bool csr_read_sie_usie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.usie;
}

__always_inline
bool csr_read_sie_utie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.utie;
}

__always_inline
bool csr_read_sie_ueie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.ueie;
}

__always_inline
bool csr_read_sie_ssie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.ssie;
}

__always_inline
bool csr_read_sie_stie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.stie;
}

__always_inline
bool csr_read_sie_seie(void)
{
	struct sie sie;
	sie.value = csr_read_sie();
	return sie.seie;
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

