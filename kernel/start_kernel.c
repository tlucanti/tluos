
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/console.h>
#include <sys/riscv.h>

__aligned(16)
uint8 _kernel_stack[4096];

extern void trap_init(void);
extern void init(void);
__noreturn void start_user(void);

__noreturn
void start_kernel(void)
{
	console_init();
	console_puts("=== kernel ===\n");
	console_puts("kernel starting\n");
	trap_init();
	rv_ecall();

	start_user();
}

__noreturn
void start_user(void)
{
	csr_write_mepc((uint64)init); // set return address for mret
	csr_write_mstatus_mpp(MSTATUS_MPP_M); // set previous mode to M mode for mret
	csr_write_mstatus_mpie(true); // set previous interrupt enable to true from mret
	rv_mret();
}
