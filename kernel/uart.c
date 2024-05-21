/**
 * UART 16550 driver
 */

#include <kernel/types.h>
#include <kernel/ops.h>
#include <sys/uart.h>

#define UART_BASE 0x10000000

#define UART_THR_REG 0x0
#define UART_RBR_REG 0x0
#define UART_LSR_REG 0x5

#define UART_LSR_DR_OFFSET       0
#define UART_LSR_DR_WIDTH        1

#define UART_LSR_TX_EMPTY_OFFSET 5
#define UART_LSR_TX_EMPTY_WIDTH  1

static bool is_data_avaliable(void)
{
	uint8 lsr;
	bool data_avaliable;

	/* read UART Line Status Register */
	lsr = read8(UART_BASE + UART_LSR_REG);

	/* get Data Ready bit from LSR */
	data_avaliable = extract(lsr, UART_LSR_DR_OFFSET, UART_LSR_DR_WIDTH);

	return data_avaliable;
}

static bool is_tx_empty(void)
{
	uint8 lsr;
	bool tx_empty;

	/* read UART Line Status Register */
	lsr = read8(UART_BASE + UART_LSR_REG);

	/* get Transmit FIFO empty register */
	tx_empty = extract(lsr, UART_LSR_TX_EMPTY_OFFSET, UART_LSR_TX_EMPTY_WIDTH);

	return tx_empty;
}

void uart_init(void)
{
}

char uart_getc(void)
{
	return read8(UART_BASE + UART_RBR_REG);
}

void uart_putc(char c)
{
	write8(UART_BASE + UART_THR_REG, c);
}

void uart_write_barrier(void)
{
	/* loop while Transmit FIFO is not empty */
	while (!is_tx_empty()) {}
}

void uart_wait_for_data(void)
{
	/* loop while data not ready */
	while (!is_data_avaliable()) {}
}

