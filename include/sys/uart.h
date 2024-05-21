
#ifndef SYS_UART_H
#define SYS_UART_H

void uart_init(void);
char uart_getc(void);
void uart_putc(char c);
void uart_write_barrier(void);
void uart_wait_for_data(void);

#endif /* SYS_UART_H */

