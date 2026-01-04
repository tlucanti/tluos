
#ifndef SYS_KALLOC_H
#define SYS_KALLOC_H

void kalloc_init(void);
void *kalloc_page(void);
void kfree_page(void *page);

#endif /* SYS_KALLOC_H */

