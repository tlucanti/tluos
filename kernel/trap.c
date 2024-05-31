
#include <sys/kconsole.h>
#include <sys/riscv.h>

extern void kernelvec(void);

void trap_handler(void)
{
	kconsole_puts("kernel trap\n");

	/*
	 * return from trap to the next instruction,
	 * after one, that caused the trap
	 */
	csr_write_mepc(csr_read_mepc() + 4);
}

void trap_init(void)
{
	csr_write_mtvec((uint64)kernelvec);
}

