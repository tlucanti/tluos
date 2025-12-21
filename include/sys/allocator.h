
#ifndef SYS_ALLOCATOR_H
#define SYS_ALLOCATOR_H

void allocator_init(void);
void *alloc_physical_page(void);
void free_physical_page(void *page);

#endif /* SYS_ALLOCATOR_H */
