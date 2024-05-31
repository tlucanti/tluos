
#include <sys/console.h>
#include <sys/riscv.h>

extern void kernelvec(void);

void trap_handler(void)
{
	console_puts("kernel trap handler, trap cause: ");
	console_putuint(csr_read_mcause());
	console_putc('\n');

	csr_write_mepc(csr_read_mepc() + 4);
}

void trap_init(void)
{
	csr_write_mtvec((uint64)kernelvec);
}

