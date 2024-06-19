
#ifndef SYS_RISCV_H
# define SYS_RISCV_H

#include <kernel/attributes.h>
#include <kernel/types.h>

struct misa_extensions {
	union {
		uint64 value;
		struct {
			uint64 A : 1;
			uint64 B : 1;
			uint64 C : 1;
			uint64 D : 1;
			uint64 E : 1;
			uint64 F : 1;
			uint64 G : 1;
			uint64 H : 1;
			uint64 I : 1;
			uint64 J : 1;
			uint64 K : 1;
			uint64 L : 1;
			uint64 M : 1;
			uint64 N : 1;
			uint64 O : 1;
			uint64 P : 1;
			uint64 Q : 1;
			uint64 R : 1;
			uint64 S : 1;
			uint64 T : 1;
			uint64 U : 1;
			uint64 V : 1;
			uint64 W : 1;
			uint64 X : 1;
			uint64 Y : 1;
			uint64 Z : 1;
		};
	};
};

enum misa_xlen {
	MISA_XLEN_32 =  0b01,
	MISA_XLEN_64 =  0b10,
	MISA_XLEN_128 = 0b11,
};

enum mstatus_mpp {
	MSTATUS_MPP_U = 0b00,
	MSTATUS_MPP_S = 0b01,
	MSTATUS_MPP_M = 0b11,
};

enum mstatus_fs {
	MSTATUS_FS_OFF     = 0b00,
	MSTATUS_FS_INITIAL = 0b01,
	MSTATUS_FS_CLEAN   = 0b10,
	MSTATUS_FS_DIRTY   = 0b11,
};

enum mstatus_xs {
	MSTATUS_XS_ALL_OFF    = 0b00,
	MSTATUS_XS_SOME_ON    = 0b01,
	MSTATUS_XS_SOME_CLEAN = 0b10,
	MSTATUS_XS_SOME_DIRTY = 0b11,
};

enum mcause_exception_code {
	MCAUSE_INTERRUPT_BIT = (1ul << 63),

	MCAUSE_USER_SOFTWARE_INTERRUPT		= 0  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_SUPERVISOR_SOFTWARE_INTERRUPT	= 1  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_MACHINE_SOFTWARE_INTRRUPT	= 3  | MCAUSE_INTERRUPT_BIT,

	MCAUSE_USER_TIMER_INTERRUPT		= 4  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_SUPERVISOR_TIMER_INTERRUPT	= 5  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_MACHINE_TIMER_INTERRUPT		= 7  | MCAUSE_INTERRUPT_BIT,

	MCAUSE_USER_EXTERNAL_INTERRUPT		= 8  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_SUPERVISOR_EXTERNAL_INTERRUPT	= 9  | MCAUSE_INTERRUPT_BIT,
	MCAUSE_MACHINE_EXTENAL_INTERRUPT	= 11 | MCAUSE_INTERRUPT_BIT,

	MCAUSE_INSTRUCTION_ADDRESS_MISALIGNED	= 0,
	MCAUSE_INSTRUCTION_ACCESS_FAULT		= 1,
	MCAUSE_ILLEGAL_INSTRUCTION		= 2,
	MCAUSE_BREAKPOINT			= 3,
	MCAUSE_LOAD_ADDRESS_MISALIGNED		= 4,
	MCAUSE_LOAD_ACCESS_FAULT		= 5,
	MCAUSE_STORE_ADDRESS_MISALIGNED		= 6,
	MCAUSE_STORE_ACCESS_FAULT		= 7,
	MCAUSE_ECALL_FROM_USER			= 8,
	MCAUSE_ECALL_FROM_SUPERVISOR		= 9,
	MCAUSE_ECALL_FROM_MACHINE		= 11,
	MCAUSE_INSTRUCTION_PAGE_FAULT		= 12,
	MCAUSE_LOAD_PAGE_FAULT			= 13,
	MCAUSE_STORE_PAGE_FAULT			= 14,
};

enum sstatus_fs {
	SSTATUS_FS_OFF     = 0b00,
	SSTATUS_FS_INITIAL = 0b01,
	SSTATUS_FS_CLEAN   = 0b10,
	SSTATUS_FS_DIRTY   = 0b11,
};

enum sstatus_xs {
	SSTATUS_XS_ALL_OFF    = 0b00,
	SSTATUS_XS_SOME_ON    = 0b01,
	SSTATUS_XS_SOME_CLEAN = 0b10,
	SSTATUS_XS_SOME_DIRTY = 0b11,
};

enum satp_mode {
	SATP_MODE_TRANSLATION_DISABLED = 0,
	SATP_MODE_39_BIT_VIRTUAL_ADDRESS = 8,
	SATP_MODE_48_BIT_VIRTUAL_ADDRESS = 9,
};

// ****************************************************************************
// RISC-V instructions mapping
// ****************************************************************************

void rv_ecall(void);
void rv_wfi(void);
__noreturn void rv_mret(void);

// ****************************************************************************
// Machine mode registers
// ****************************************************************************

/**
 * machine information registers
 */

/* read registers */
uint64 csr_read_mvendorid(void);

uint64 csr_read_marchid(void);

uint64 csr_read_mimpid(void);

uint64 csr_read_mhartid(void);


/**
 * machine trap setup
 */

/* read registers */
uint64 csr_read_mstatus(void);
	bool csr_read_mstatus_uie(void);
	bool csr_read_mstatus_upie(void);
	bool csr_read_mstatus_sie(void);
	bool csr_read_mstatus_spie(void);
	bool csr_read_mstatus_spp(void);
	bool csr_read_mstatus_sum(void);
	bool csr_read_mstatus_sd(void);
	bool csr_read_mstatus_mie(void);
	bool csr_read_mstatus_mpie(void);
	enum mstatus_mpp csr_read_mstatus_mpp(void);
	bool csr_read_mstatus_mprv(void);
	bool csr_read_mstatus_mxr(void);
	enum mstatus_fs csr_read_mstatus_fs(void);
	enum mstatus_xs csr_read_mstatus_xs(void);

uint64 csr_read_misa(void);
	struct misa_extensions csr_read_misa_extensions(void);

uint64 csr_read_mie(void);
	bool csr_read_mie_usie(void);
	bool csr_read_mie_utie(void);
	bool csr_read_mie_ueie(void);
	bool csr_read_mie_stie(void);
	bool csr_read_mie_seie(void);
	bool csr_read_mie_ssie(void);
	bool csr_read_mie_msie(void);
	bool csr_read_mie_mtie(void);
	bool csr_read_mie_meie(void);


/* write registers */
void csr_write_medeleg(uint64 x);

void csr_write_mideleg(uint64 x);

void csr_write_mstatus(uint64 x);
	void csr_write_mstatus_uie(bool enable);
	void csr_write_mstatus_upie(bool enable);
	void csr_write_mstatus_sie(bool enable);
	void csr_write_mstatus_spie(bool enable);
	void csr_write_mstatus_spp(bool enable);
	void csr_write_mstatus_sum(bool enable);
	void csr_write_mstatus_sd(bool enable);
	void csr_write_mstatus_mie(bool enable);
	void csr_write_mstatus_mpie(bool enable);
	void csr_write_mstatus_mpp(enum mstatus_mpp mpp);
	void csr_write_mstatus_mprv(bool enable);
	void csr_write_mstatus_mxr(bool enable);
	void csr_write_mstatus_fs(enum mstatus_fs fs);
	void csr_write_mstatus_xs(enum mstatus_xs xs);

void csr_write_mie(uint64 x);
	void csr_write_mie_usie(bool enable);
	void csr_write_mie_utie(bool enable);
	void csr_write_mie_ueie(bool enable);
	void csr_write_mie_ssie(bool enable);
	void csr_write_mie_stie(bool enable);
	void csr_write_mie_seie(bool enable);
	void csr_write_mie_msie(bool enable);
	void csr_write_mie_mtie(bool enable);
	void csr_write_mie_meie(bool enable);

void csr_write_mtvec(uint64 x);


/**
 * machine trap handling
 */

/* read registers */
uint64 csr_read_mscratch(void);

uint64 csr_read_mepc(void);

uint64 csr_read_mcause(void);

uint64 csr_read_mtval(void);


/* write registers */
void csr_write_mscratch(uint64 x);

void csr_write_mepc(uint64 x);


/**
 * machine protection and translation
 */

/* write registers */
void csr_write_pmpcfg0(uint64 x);
	void csr_write_pmp0cfg(uint8 flags);
	void csr_write_pmp1cfg(uint8 flags);
	void csr_write_pmp2cfg(uint8 flags);
	void csr_write_pmp3cfg(uint8 flags);
	void csr_write_pmp4cfg(uint8 flags);
	void csr_write_pmp5cfg(uint8 flags);
	void csr_write_pmp6cfg(uint8 flags);
	void csr_write_pmp7cfg(uint8 flags);

void csr_write_pmpcfg2(uint64 x);
	void csr_write_pmp8cfg(uint8 flags);
	void csr_write_pmp9cfg(uint8 flags);
	void csr_write_pmp10cfg(uint8 flags);
	void csr_write_pmp11cfg(uint8 flags);
	void csr_write_pmp12cfg(uint8 flags);
	void csr_write_pmp13cfg(uint8 flags);
	void csr_write_pmp14cfg(uint8 flags);
	void csr_write_pmp15cfg(uint8 flags);

void csr_write_pmpaddr0(uint64 address);
void csr_write_pmpaddr1(uint64 address);
void csr_write_pmpaddr2(uint64 address);
void csr_write_pmpaddr3(uint64 address);
void csr_write_pmpaddr4(uint64 address);
void csr_write_pmpaddr5(uint64 address);
void csr_write_pmpaddr6(uint64 address);
void csr_write_pmpaddr7(uint64 address);
void csr_write_pmpaddr8(uint64 address);
void csr_write_pmpaddr9(uint64 address);
void csr_write_pmpaddr10(uint64 address);
void csr_write_pmpaddr11(uint64 address);
void csr_write_pmpaddr12(uint64 address);
void csr_write_pmpaddr13(uint64 address);
void csr_write_pmpaddr14(uint64 address);
void csr_write_pmpaddr15(uint64 address);


// ****************************************************************************
// Supervisor mode registers
// ****************************************************************************

/**
 * supervisor trap setup
 */

/* read registers */
uint64 csr_read_sstatus(void);
	bool csr_read_sstatus_uie(void);
	bool csr_read_sstatus_upie(void);
	bool csr_read_sstatus_sie(void);
	bool csr_read_sstatus_spie(void);
	bool csr_read_sstatus_spp(void);
	bool csr_read_sstatus_sum(void);
	bool csr_read_sstatus_sd(void);
	bool csr_read_sstatus_mxr(void);
	enum sstatus_fs csr_read_sstatus_fs(void);
	enum sstatus_xs csr_read_sstatus_xs(void);

uint64 csr_read_sie(void);
	bool csr_read_sie_usie(void);
	bool csr_read_sie_utie(void);
	bool csr_read_sie_ueie(void);
	bool csr_read_sie_stie(void);
	bool csr_read_sie_seie(void);
	bool csr_read_sie_ssie(void);


/* write registers */
void csr_write_sedeleg(uint64 x);

void csr_write_sideleg(uint64 x);

void csr_write_sie(uint64 x);

void csr_write_stvec(uint64 x);


/**
 * supervisor trap handling
 */

/* read registers */
uint64 csr_read_sscratch(void);

uint64 csr_read_sepc(void);

uint64 csr_read_scause(void);

uint64 csr_read_stval(void);


/* write registers */
void csr_write_sscratch(uint64 x);

void csr_write_sepc(uint64 x);


/**
 * supervisor protection and translation
 */

/* read registers */
uint64 csr_read_satp(void);
	uint64 csr_read_satp_ppn(void);
	uint64 csr_read_satp_asid(void);
	enum satp_mode csr_read_satp_mode(void);


/* write registers */
void csr_write_satp(uint64 x);
	void csr_write_satp_ppn(uint64 x);
	void csr_write_satp_asid(uint64 x);
	void csr_write_satp_mode(enum satp_mode);


#endif /* SYS_RISCV_H */

