
#include <stdint.h>

__attribute__((__aligned__(16))) char *_kernel_stack[4096];
__attribute__((__aligned__(16))) uint64_t timer_scratch[16];

#define UART		(volatile unsigned char *)0x10000000
#define MTIME		(volatile uint64_t *)0x200bff8
#define MTIMECMP	(volatile uint64_t *)0x2004000

#define MSTATUS_MIE	0x8
#define MIE_MTIE	0x80

#define TIMER_INTERVAL	10000000

extern void timervec(void);

static void write_mtvec(uint64_t val)
{
	__asm__ volatile("csrw mtvec, %0" : : "r" (val));
}

static uint64_t read_mstatus(void)
{
	uint64_t x;
	__asm__ volatile("csrr %0, mstatus" : "=r"(x));
	return x;
}

static void write_mstatus(uint64_t val)
{
	__asm__ volatile("csrw mstatus, %0" : : "r" (val));
}

static uint64_t read_mie(void)
{
	uint64_t x;
	__asm__ volatile("csrr %0, mie" : "=r"(x));
	return x;
}

static void write_mie(uint64_t val)
{
	__asm__ volatile("csrw mie, %0" : : "r" (val));
}

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

static void timerinit(void)
{
	write_mtvec((uint64_t)timervec);
	write_mstatus(read_mstatus() | MSTATUS_MIE);
	write_mie(read_mie() | MIE_MTIE);
}

static void alarm(uint64_t nr_ticks)
{
	uint64_t current_time = *MTIME;
	uint64_t alarm_time = current_time + nr_ticks;
	*MTIMECMP = alarm_time;
}

void start_kernel()
{
	alarm(TIMER_INTERVAL);
	timerinit();
	while (1);
}

