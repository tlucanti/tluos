
#ifndef SYS_MMU_H
#define SYS_MMU_H

#include <kernel/err.h>
#include <kernel/ops.h>

enum {
	PTE_V = BIT(0),
	PTE_R = BIT(1),
	PTE_W = BIT(2),
	PTE_X = BIT(3),
};

typedef enum {
	PAGE_PERM_RO     = PTE_R | PTE_V,
	PAGE_PERM_RW     = PTE_R | PTE_W | PTE_V,
	PAGE_PERM_EXEC   = PTE_R | PTE_X | PTE_V,
	PAGE_PERM_KERNEL = PTE_R | PTE_W | PTE_X | PTE_V,
} PagePerm;

void mmu_init(void);
void mmap_kernel_space(void);
void mmu_enable(void);

#endif /* SYS_MMU_H */
