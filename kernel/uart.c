
/**
 * UART 16550a low level driver
 */

#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/uart.h>

#define UART_BASE 0x10000000

#define UART_RBR (UART_BASE + 0x00)
#define UART_IER (UART_BASE + 0x01)
#define UART_IIR (UART_BASE + 0x02)
#define UART_LCR (UART_BASE + 0x03)
#define UART_MCR (UART_BASE + 0x04)
#define UART_LSR (UART_BASE + 0x05)
#define UART_MSR (UART_BASE + 0x06)
#define UART_SCR (UART_BASE + 0x07)

#define UART_THR (UART_BASE + 0x00)
#define UART_FCR (UART_BASE + 0x02)

#define UART_DLL (UART_BASE + 0x00)
#define UART_DLM (UART_BASE + 0x01)

#define UART_LCR_DLAB_ENABLE	(1 << 7)
#define UART_LSR_DATA_AVALIABLE	(1 << 0)
#define UART_LSR_THR_EMPTY	(1 << 5)

#define WRITE_BYTE(ptr, val)						\
	do {								\
		*(volatile uint8 *)(ptr) = *(volatile uint8 *)(val);	\
	} while (false)

#define READ_BYTE(ptr) ({ *(volatile uint8 *)(ptr); })

/**
 * UART direct register interface
 */

/* read registers */
__maybe_unused __always_inline
static uint8 reg_read_rbr(void)
{
	return READ_BYTE(UART_RBR);
}

__maybe_unused __always_inline
static uint8 reg_read_ier(void)
{
	return READ_BYTE(UART_IER);
}

__maybe_unused __always_inline
static uint8 reg_read_iir(void)
{
	return READ_BYTE(UART_IIR);
}

__maybe_unused __always_inline
static uint8 reg_read_lcr(void)
{
	return READ_BYTE(UART_LCR);
}

__maybe_unused __always_inline
static uint8 reg_read_mcr(void)
{
	return READ_BYTE(UART_MCR);
}

__maybe_unused __always_inline
static uint8 reg_read_lsr(void)
{
	return READ_BYTE(UART_LSR);
}

__maybe_unused __always_inline
static uint8 reg_read_msr(void)
{
	return READ_BYTE(UART_MSR);
}

__maybe_unused __always_inline
static uint8 reg_read_scr(void)
{
	return READ_BYTE(UART_SCR);
}

/* write registers */
__maybe_unused __always_inline
static void reg_write_thr(uint8 val)
{
	WRITE_BYTE(UART_THR, &val);
}

__maybe_unused __always_inline
static void reg_write_ier(uint8 val)
{
	WRITE_BYTE(UART_IER, &val);
}

__maybe_unused __always_inline
static void reg_write_fcr(uint8 val)
{
	WRITE_BYTE(UART_FCR, &val);
}

__maybe_unused __always_inline
static void reg_write_lcr(uint8 val)
{
	WRITE_BYTE(UART_LCR, &val);
}

__maybe_unused __always_inline
static void reg_write_mcr(uint8 val)
{
	WRITE_BYTE(UART_MCR, &val);
}

__maybe_unused __always_inline
static void reg_write_scr(uint8 val)
{
	WRITE_BYTE(UART_SCR, &val);
}

/* DLAB read registers */
__maybe_unused __always_inline
static uint8 reg_read_dll(void)
{
	return READ_BYTE(UART_DLL);
}

__maybe_unused __always_inline
static uint8 reg_read_dlm(void)
{
	return READ_BYTE(UART_DLM);
}

/* DLAB write registers */
__maybe_unused __always_inline
static void reg_write_dll(uint8 val)
{
	WRITE_BYTE(UART_DLL, &val);
}

__maybe_unused __always_inline
static void reg_write_dlm(uint8 val)
{
	WRITE_BYTE(UART_DLM, &val);
}

/**
 * UART low level feature interface
 */

__maybe_unused __always_inline
static void uart_enable_dlab(void)
{
	unsigned char val = reg_read_lcr();

	val |= UART_LCR_DLAB_ENABLE;
	reg_write_lcr(val);
}

__maybe_unused __always_inline
static void uart_disable_dlab(void)
{
	unsigned char val = reg_read_lcr();

	val &= ~UART_LCR_DLAB_ENABLE;
	reg_write_lcr(val);
}

__maybe_unused __always_inline
static bool uart_tx_empty(void)
{
	return reg_read_lsr() & UART_LSR_THR_EMPTY;
}

__maybe_unused __always_inline
static bool uart_data_avaliable(void)
{
	return reg_read_lsr() & UART_LSR_DATA_AVALIABLE;
}

/**
 * UART public configuration interface
 */

inline void uart_disable_interrupts(void)
{
	reg_write_ier(0);
}

inline void uart_set_baud_rate(enum uart_baud_rate baud_rate)
{
	const uint8 dll_lut[10] = { 0x09, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	const uint8 dlm_lut[10] = { 0x00, 0x80, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x02, 0x01 };

	if (unlikely(baud_rate > UART_BAUD_RATE_115200)) {
		baud_rate = UART_BAUD_RATE_4800;
	}

	uart_enable_dlab();
	reg_write_dll(dll_lut[baud_rate]);
	reg_write_dlm(dlm_lut[baud_rate]);
	uart_disable_dlab();
}

inline char uart_getc(void)
{
	return reg_read_rbr();
}

inline void uart_putc(char c)
{
	reg_write_thr(c);
}

inline void uart_write_barrier(void)
{
	while (!uart_tx_empty()) {}
}

inline void uart_wait_for_data(void)
{
	while (!uart_data_avaliable()) {}
}

