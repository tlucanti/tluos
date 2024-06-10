
#include <kernel/task.h>
#include <sys/console.h>
#include <sys/riscv.h>

extern void kernelvec(void);
extern void syscall();

__aligned(16) extern uint8 _kernel_stack[4096];

void trap_handler(void)
{
	switch (csr_read_mcause()) {
	case 11:
		syscall();
		break;
	default:
		console_puts("unexpected kernel trap: ");
		console_putuint(csr_read_mcause());
		console_putc('\n');
		break;
	}

	csr_write_mepc(csr_read_mepc() + 4);
}

void trap_init(void)
{
	csr_write_mtvec((uint64)kernelvec);
}
