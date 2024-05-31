
#ifndef KERNEL_CONSOLE_H
#define KERNEL_CONSOLE_H

#include <kernel/types.h>

uint console_init(void);
char console_getc(void);
uint console_putc(char c);
uint console_puts(const char *s);
uint console_putint(int64 x);
uint console_putuint(uint64 x);

#endif /* KERNEL_CONSOLE_H */

