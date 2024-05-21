
#ifndef KERNEL_KCONSOLE_H
#define KERNEL_KCONSOLE_H

void kconsole_init(void);
char kconsole_getc(void);
void kconsole_putc(char c);
void kconsole_puts(const char *s);

#endif /* KERNEL_KCONSOLE_H */

