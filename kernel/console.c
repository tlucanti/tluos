
#include <sys/uart.h>

void console_init(void)
{
	uart_disable_interrupts();
	uart_set_baud_rate(UART_BAUD_RATE_38400);
}

char console_getc(void)
{
	uart_wait_for_data();
	return uart_getc();
}

void console_putc(char c)
{
	uart_putc(c);
	uart_write_barrier();
}

void console_puts(const char *s)
{
	while (*s) {
		console_putc(*s);
		s++;
	}
}

