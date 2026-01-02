
#include <kernel/types.h>
#include <kernel/attributes.h>

#include <sys/kconsole.h>
#include <sys/ktime.h>
#include <sys/riscv.h>

__aligned(16)
uint8 _kernel_stack[4096];

extern void trap_init(void);

static void echo_loop(void)
{
	while (true) {
		char c;

		c = kconsole_getc();
		if (c == '\r') {
			/*
			 * when pressing Enter key - UART will receive \r
			 * character, so we need to send \n instead to
			 * write new line
			 */
			kconsole_putc('\n');
		} else if (c == 127) {
			/*
			 * when pressing Backspace key - UART will receive
			 * DEL character (ASCII 127 number), so to clear
			 * last character - we should send \b to move cursor
			 * to one position left, then send space to replace
			 * last character with blank, and then send \b again
			 * to move cursor to position before just printed
			 * space
			 */
			kconsole_puts("\b \b");
		} else {
			/* otherwise - just send back what UART received */
			kconsole_putc(c);
		}
	}
}

void main()
{
	trap_init();
	ktime_init();

	kconsole_init();

	kconsole_puts("Hello, kernel\n");

	/* check interrupt system */
	rv_ecall();

	/* set timer to fire in one second */
	ktime_set_timer(1 * NS_IN_S);

	echo_loop();
}

void start_kernel(void)
{
	csr_write_medeleg(MASK(0, 16));
	csr_write_mideleg(MASK(0, 16));

	csr_write_mstatus_mpp(MSTATUS_MPP_S);
	csr_write_mepc((uint64)main);

	csr_write_pmpaddr0(MASK(0, 54));
	csr_write_pmp0cfg(PMPCFG_R | PMPCFG_W | PMPCFG_X | PMPCFG_TOR);

	csr_write_menvcfg_stce(true);
	csr_write_mcounteren_tm(true);

	rv_mret();
}

