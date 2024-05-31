
#include <kernel/types.h>
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

uint console_putc(char c)
{
	uart_putc(c);
	uart_write_barrier();
	return 1;
}

uint console_puts(const char *s)
{
	uint n = 0;
	while (s[n]) {
		console_putc(s[n]);
		n++;
	}
	return n;
}

uint console_putint(int64 x)
{
	char buf[22];
	uint i = 21;
	const bool negative = x < 0;

	if (x == 0) {
		console_putc('0');
		return 1;
	}

	buf[i--] = '\0';
	while (x) {
		if (negative) {
			buf[i--] = -(x % 10) + '0';
		} else {
			buf[i--] = x % 10 + '0';
		}
		x /= 10;
	}
	if (negative) {
		buf[i--] = '-';
	}

	console_puts(buf + i + 1);
	return 20 - i;
}

uint console_putuint(uint64 x)
{
	char buf[22];
	uint i = 21;

	if (x == 0) {
		console_putc('0');
		return 1;
	}

	buf[i--] = 0;
	while (x) {
		buf[i--] = x % 10 + '0';
		x /= 10;
	}

	console_puts(buf + i + 1);
	return 20 - i;
}
