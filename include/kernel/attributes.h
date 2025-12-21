
#ifndef KERNEL_ATTRIBUTES_H
#define KERNEL_ATTRIBUTES_H

#define PAGE_SIZE 4096

#define __aligned(x) __attribute__((__aligned__(x)))

#define __noreturn __attribute__((__noreturn__))

#endif /* KERNEL_ATTRIBUTES_H */

