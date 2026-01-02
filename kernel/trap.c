
#include <kernel/ops.h>
#include <kernel/panic.h>
#include <kernel/types.h>

#include <sys/kconsole.h>
#include <sys/riscv.h>
#include <sys/ktime.h>

extern void kernelvec(void);

enum {
	SCAUSE_INTERRUPT_BIT    = BIT(63),

	SCAUSE_ECALL_FROM_SMODE = 9,
	SCAUSE_STIMER_INTERRUPT = 5 | SCAUSE_INTERRUPT_BIT,
};

void trap_handler(void)
{
	switch (csr_read_scause()) {
	case SCAUSE_ECALL_FROM_SMODE:
		kconsole_puts("ecall trap\n");

		/* return from trap to the next instruction after ecall one */
		csr_write_sepc(csr_read_sepc() + 4);
		break;

	case SCAUSE_STIMER_INTERRUPT:
		kconsole_puts("timer interrupt\n");

		/* set next timer in about one second */
		ktime_set_timer(1 * NS_IN_S);

		/*
		 * keep return instructino to the one, that was interrupted,
		 * because it was not executed
		 */
		break;

	default:
		panic("unexpected interrupt");
	}
}

void trap_init(void)
{
	csr_write_stvec((uint64)kernelvec);
}
