
#ifndef KERNEL_CONSOLE_H
#define KERNEL_CONSOLE_H

void console_init(void);
char console_getc(void);
void console_putc(char c);
void console_puts(const char *s);

#endif /* KERNEL_CONSOLE_H */

