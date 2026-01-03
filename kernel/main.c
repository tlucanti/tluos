
#include <kernel/types.h>

#include <sys/kconsole.h>
#include <sys/ktime.h>
#include <sys/riscv.h>

extern void trap_init(void);

void echo_loop(void)
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

void main(void)
{
	kconsole_init();
	trap_init();
	ktime_init();

	kconsole_puts("Hello, kernel\n");

	rv_ecall();

	/* set timer to fire in one second */
	ktime_set_timer(1 * NS_IN_S);

	echo_loop();
}
