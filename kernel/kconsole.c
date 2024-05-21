
#include <sys/uart.h>

void kconsole_init(void)
{
	uart_init();
}

char kconsole_getc(void)
{
	uart_wait_for_data();
	return uart_getc();
}

void kconsole_putc(char c)
{
	uart_putc(c);
	uart_write_barrier();
}

void kconsole_puts(const char *s)
{
	while (*s) {
		kconsole_putc(*s);
		s++;
	}
}

