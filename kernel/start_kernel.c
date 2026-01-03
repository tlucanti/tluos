
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/riscv.h>

__aligned(16)
uint8 _kernel_stack[4096];

extern void main(void);

void start_kernel(void)
{
	csr_write_pmpaddr0(MASK(0, 54));
	csr_write_pmp0cfg(PMPCFG_R | PMPCFG_W | PMPCFG_X | PMPCFG_TOR);

	csr_write_medeleg(MASK(0, 16));
	csr_write_mideleg(MASK(0, 16));

	csr_write_mstatus_mpp(MSTATUS_MPP_S);
	csr_write_mepc((uint64)main);

	rv_mret();
}

