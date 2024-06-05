
#include <kernel/task.h>
#include <sys/console.h>
#include <sys/riscv.h>

extern void kernelvec(void);
extern void syscall();

__aligned(16)
extern uint8 _kernel_stack[4096];

struct frame trapframe;

void trap_handler(void)
{
	console_puts("=== kernel trap handler ===\n");
	console_puts("trap cause: ");
	switch (csr_read_mcause()) {
	case 11:
		console_puts("ecall from mmode\n");
		syscall();
		break;
	default:
		console_putuint(csr_read_mcause());
		break;
	}

	csr_write_mepc(csr_read_mepc() + 4);
	console_puts("=== back to user space ===\n");
}

void trap_init(void)
{
	csr_write_mtvec((uint64)kernelvec);
}
