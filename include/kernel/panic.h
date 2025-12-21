
#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <kernel/attributes.h>

__noreturn
void panic(char *message);

#endif /* KERNEL_PANIC_H */
