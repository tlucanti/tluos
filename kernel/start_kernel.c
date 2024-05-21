
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/console.h>

__aligned(16)
uint8 _kernel_stack[4096];

void start_kernel(void)
{
	console_init();

	while (true) {
		console_puts("read >> ");
		console_putc(console_getc());
		console_putc('\n');
	}
}

