
#include <kernel/ops.h>
#include <kernel/panic.h>
#include <kernel/types.h>

#include <sys/kconsole.h>
#include <sys/riscv.h>
#include <sys/ktime.h>

extern void kernelvec(void);

enum {
	MCAUSE_INTERRUPT_BIT    = BIT(63),

	MCAUSE_ECALL_FROM_MMODE = 11,
	MCAUSE_MTIMER_INTERRUPT = 7 | MCAUSE_INTERRUPT_BIT,
};

void trap_handler(void)
{
	switch (csr_read_mcause()) {
	case MCAUSE_ECALL_FROM_MMODE:
		kconsole_puts("ecall trap\n");

		/* return from trap to the next instruction after ecall one */
		csr_write_mepc(csr_read_mepc() + 4);
		break;

	case MCAUSE_MTIMER_INTERRUPT:
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
	csr_write_mtvec((uint64)kernelvec);
}
