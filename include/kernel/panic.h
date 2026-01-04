
#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <kernel/attributes.h>
#include <kernel/err.h>

__noreturn
void panic(char *message);

void panic_on(Error err, const char *message);

#endif /* KERNEL_PANIC_H */
