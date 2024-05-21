
#ifndef SYS_UART_H
#define SYS_UART_H

enum uart_baud_rate {
	UART_BAUD_RATE_50,
	UART_BAUD_RATE_300,
	UART_BAUD_RATE_1200,
	UART_BAUD_RATE_2400,
	UART_BAUD_RATE_4800,
	UART_BAUD_RATE_9600,
	UART_BAUD_RATE_19200,
	UART_BAUD_RATE_38400,
	UART_BAUD_RATE_57600,
	UART_BAUD_RATE_115200,
};

void uart_disable_interrupts(void);
void uart_set_baud_rate(enum uart_baud_rate baud_rate);
char uart_getc(void);
void uart_putc(char c);
void uart_write_barrier(void);
void uart_wait_for_data(void);

#endif /* SYS_UART_H */

