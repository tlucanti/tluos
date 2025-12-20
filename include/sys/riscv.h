
#ifndef SYS_RISCV_H
# define SYS_RISCV_H

#include <kernel/types.h>

void rv_ecall(void);

uint64 csr_read_mepc(void);
void csr_write_mepc(uint64 x);

void csr_write_mtvec(uint64 x);

uint64 csr_read_mcause(void);

uint64 csr_read_mstatus(void);
void csr_write_mstatus(uint64 x);
void csr_write_mstatus_mie(bool enable);

uint64 csr_read_mie(void);
void csr_write_mie(uint64 x);
void csr_write_mie_mtie(bool enable);

#endif /* SYS_RISCV_H */

