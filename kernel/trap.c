
#include <kernel/kprint.h>
#include <kernel/ktime.h>
#include <kernel/task.h>
#include <sys/riscv.h>

extern void kernelvec(void);
extern void syscall();
extern void sys_sched(void);

__aligned(16) extern uint8 _kernel_stack[4096];

void trap_handler(void)
{
	switch (csr_read_mcause()) {
	case MCAUSE_ECALL_FROM_MACHINE:
		syscall();
		csr_write_mepc(csr_read_mepc() + 4);
		break;
	case MCAUSE_MACHINE_TIMER_INTERRUPT:
		klog("timer interrupt");
		sys_sched();
		ktimer_set(ktime() + (uint64)1e7);
		csr_write_mepc(csr_read_mepc() + 4);
		break;
	default:
		klog("unexpected kernel trap: %lu", csr_read_mcause());
		break;
	}
}

void trap_init(void)
{
	csr_write_mtvec((uint64)kernelvec);
}

void timer_init(void)
{
	ktimer_set(ktime() + (uint64)1e7);
	csr_write_mstatus_mie(true);
	csr_write_mie_mtie(true);
}
