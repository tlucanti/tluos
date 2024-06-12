
#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H

#include <kernel/types.h>
#include <kernel/attributes.h>

__printf(1, 0) void klog(const char *format, ...);
__printf(1, 2) uint kprint(const char *format, ...);
__printf(1, 0) uint kprintv(const char *format, va_list args);

#endif /* KERNEL_PRINK_H */
