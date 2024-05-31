
#ifndef SYS_RISCV_H
# define SYS_RISCV_H

#include <kernel/types.h>

void rv_ecall(void);

uint64 csr_read_mepc(void);
void csr_write_mepc(uint64 x);

void csr_write_mtvec(uint64 x);

#endif /* SYS_RISCV_H */

