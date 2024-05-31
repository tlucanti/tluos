
#ifndef SYS_RISCV_H
# define SYS_RISCV_H

#include <kernel/attributes.h>
#include <kernel/types.h>

enum mstatus_mpp_mode {
	MSTATUS_MPP_U = 0b00,
	MSTATUS_MPP_S = 0b01,
	MSTATUS_MPP_M = 0b11,
};

/**
 * RISC-V instructions mapping
 */
void rv_ecall(void);
void rv_wfi(void);
__noreturn void rv_mret(void);

/**
 * Machine mode registers
 */

/* machine information registers */
uint64 csr_read_mvendorid(void);
uint64 csr_read_marchid(void);
uint64 csr_read_mimpid(void);
uint64 csr_read_mhartid(void);

/* machine trap setup */
uint64 csr_read_mstatus(void);
uint64 csr_read_misa(void);
uint64 csr_read_mie(void);
uint64 csr_read_mcounteren(void);

void csr_write_medeleg(uint64 x);
void csr_write_mideleg(uint64 x);
void csr_write_mstatus(uint64 x);
void csr_write_mstatus_mpp(enum mstatus_mpp_mode mode);
void csr_write_mstatus_mpie(bool enable);
void csr_write_mie(uint64 x);
void csr_write_mtvec(uint64 x);
void csr_write_mcounteren(uint64 x);

/* machine trap handling */
uint64 csr_read_mscratch(void);
uint64 csr_read_mepc(void);
uint64 csr_read_mcause(void);
uint64 csr_read_mtval(void);
uint64 csr_read_mip(void);

void csr_write_mscratch(uint64 x);
void csr_write_mepc(uint64 x);

/* machine protection and translation */
void csr_write_pmpcfg0(uint64 x);

/* machine counter/timers */
uint64 csr_read_mcycle(void);

/**
 * Supervisor mode registers
 */

/* supervisor trap setup */
uint64 csr_read_sstatus(void);
uint64 csr_read_sie(void);
uint64 csr_read_scounteren(void);

void csr_write_sedeleg(uint64 x);
void csr_write_sideleg(uint64 x);
void csr_write_sie(uint64 x);
void csr_write_stvec(uint64 x);
void csr_write_scounteren(uint64 x);

/* supervisor trap handling */
uint64 csr_read_sscratch(void);
uint64 csr_read_sepc(void);
uint64 csr_read_scause(void);
uint64 csr_read_stval(void);
uint64 csr_read_sip(void);

void csr_write_sscratch(uint64 x);
void csr_write_sepc(uint64 x);

/* supervisor protection and translation */
uint64 csr_read_satp(void);

void csr_write_satp(uint64 x);

#endif /* SYS_RISCV_H */

