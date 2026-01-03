
#ifndef SYS_RISCV_H
#define SYS_RISCV_H

#include <kernel/ops.h>
#include <kernel/types.h>

typedef enum {
	MSTATUS_MPP_U = 0b00,
	MSTATUS_MPP_S = 0b01,
	MSTATUS_MPP_M = 0b11,
} CsrMstatusMpp;

typedef enum {
	PMPCFG_R   = BIT(0),
	PMPCFG_W   = BIT(1),
	PMPCFG_X   = BIT(2),
	PMPCFG_TOR = BIT(3),
} CsrPmpCfg;

// riscv instructions mappings

void   rv_ecall(void);
void   rv_mret(void);

// m-mode csr mapings

uint64 csr_read_mstatus(void);
void   csr_write_mstatus(uint64 mstatus);
void   csr_write_mstatus_mpp(CsrMstatusMpp mpp);
void   csr_write_medeleg(uint64 medeleg);
void   csr_write_mideleg(uint64 mideleg);
void   csr_write_mepc(uint64 mepc);

void   csr_write_pmpaddr0(uint64 pmpaddr0);
uint64 csr_read_pmpcfg0(void);
void   csr_write_pmpcfg0(uint64 pmpcfg0);
void   csr_write_pmp0cfg(CsrPmpCfg pmp0cfg);

uint64 csr_read_mcounteren(void);
void   csr_write_mcounteren(uint64 mcounteren);
void   csr_write_mcounteren_tm(bool tm);
uint64 csr_read_menvcfg(void);
void   csr_write_menvcfg(uint64 menvcfg);
void   csr_write_menvcfg_stce(bool stce);

// s-mode csr mapings

void   csr_write_stvec(uint64 stvec);
uint64 csr_read_sstatus(void);
void   csr_write_sstatus(uint64 sstatus);
void   csr_write_sstatus_sie(bool stie);
uint64 csr_read_sie(void);
void   csr_write_sie(uint64 sie);
void   csr_write_sie_stie(bool stie);
uint64 csr_read_scause(void);
uint64 csr_read_sepc(void);
void   csr_write_sepc(uint64 sepc);

uint64 csr_read_time(void);
void   csr_write_stimecmp(uint64 stimecmp);

#endif /* SYS_RISCV_H */

