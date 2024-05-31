
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/console.h>
#include <sys/riscv.h>

__aligned(16)
uint8 _kernel_stack[4096];

extern void trap_init(void);

void start_kernel(void)
{
	console_init();
	trap_init();

	rv_ecall();

	while (true) {
		console_puts("read >> ");
		console_putc(console_getc());
		console_putc('\n');
	}
}

