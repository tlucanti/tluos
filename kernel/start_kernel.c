
#include <kernel/types.h>
#include <kernel/attributes.h>

__aligned(16)
uint8 _kernel_stack[4096];

#define UART_BASE (volatile uint8 *)0x10000000

void start_kernel(void)
{
	*UART_BASE = 'h';
	*UART_BASE = 'e';
	*UART_BASE = 'l';
	*UART_BASE = 'l';
	*UART_BASE = 'o';
	*UART_BASE = '\n';
}

