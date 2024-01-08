
char *_kernel_stack[4096];

#define UART (volatile unsigned char *)0x10000000

static void uart_putc(char c)
{
	*UART = c;
}

static void uart_puts(const char *s)
{
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

void start_kernel()
{
	uart_puts("hello world\n");
}

