
#ifndef KERNEL_ALLOCATOR_H
#define KERNEL_ALLOCATOR_H

#include <kernel/types.h>

void kpage_alloc_init(void);
void *kpage_alloc(uint order);
void kpage_free(void *page, uint order);

#endif /* KERNEL_ALLOCATOR_H */


