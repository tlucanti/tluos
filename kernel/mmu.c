
#include <kernel/attributes.h>
#include <kernel/err.h>
#include <kernel/ops.h>
#include <kernel/types.h>
#include <kernel/panic.h>

#include <sys/kconsole.h>
#include <sys/allocator.h>

#define START_OF_KERNEL_TEXT 0x80000000

extern uint64 END_OF_KERNEL_TEXT;

static void *satp = NULL;

enum {
	PTE_V = BIT(0),
	PTE_R = BIT(1),
	PTE_W = BIT(2),
	PTE_X = BIT(3),
};

typedef enum {
	PAGE_PERM_RO = PTE_R | PTE_V,
	PAGE_PERM_RW = PTE_R | PTE_W | PTE_V,
	PAGE_PERM_EXEC = PTE_R | PTE_X | PTE_V,
	PAGE_PERM_KERNEL = PTE_R | PTE_W | PTE_X | PTE_V,
} PagePerm;

static Error mmap_page(uint64 virtual_addr, uint64 physical_addr, PagePerm perm)
{
	uint64 vpn2 = GET_VPN2(virtual_addr);
	uint64 vpn1 GET_VPN1(virtual_addr);
	uint64 vpn0 = GET_VPN0(virtual_addr);

	uint64 ppn2 = GET_PPN2(physical_addr);
	uint64 ppn1 = GET_PPN1(physical_addr);
	uint64 ppn0 = GET_PPN0(physical_addr);

	if (virtual_addr > SV39_MAX_ADDR) {
		panic("mmap bad addr");
	}

	if (satp == NULL) {
		satp = alloc_physical_page();
		if (satp == NULL) {
			return E_NOMEM;
		}
	}

	pagetable = satp;

	if (pagetable[vpn2] == NULL) {
		pagetable = alloc_physical_page();
		if (pagetable == NULL) {
			return E_NOMEM;
		}

		cur_ptr[vpn2] = PADDR_TO_PTE(pagetable) | PTE_V;
	} else {
		pagetable = PTE_TO_PADDR(pagetable[vpn2]);
	}

	if (pagetable[vpn1] == NULL) {
		pagetable = alloc_physical_page();
		if (pagetable == NULL) {
			return E_NOMEM;
		}

		cur_ptr[vpn1] = PADDR_TO_PTE(pagetable) | PTE_V;
	} else {
		pagetable = PTE_TO_PADDR(pagetable[vpn1]);
	}

	pagetable[vpn0] = PADDR_TO_PTE(physical_addr) | perm;

	return E_OK;
}

static void mmap_kernel_space(void)
{
	for (uint64 page = START_OF_KERNEL_TEXT;
	     page < END_OF_KERNEL_TEXT;
	     page += PAGE_SIZE) {

		mmap_page(page, page, PAGE_PERM_KERNEL);
	}
}

void mmu_init(void)
{
}

