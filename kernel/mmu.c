
#include <kernel/attributes.h>
#include <kernel/err.h>
#include <kernel/ops.h>
#include <kernel/types.h>
#include <kernel/panic.h>

#include <sys/kalloc.h>
#include <sys/mmu.h>
#include <sys/riscv.h>

#define SV39_MAX_ADDR (BIT(39) - 1)

#define SV39_VPN2_OFFSET 30
#define SV39_VPN1_OFFSET 21
#define SV39_VPN0_OFFSET 12

#define SV39_VPN2_WIDTH 9
#define SV39_VPN1_WIDTH 9
#define SV39_VPN0_WIDTH 9

#define PADDR_TO_PTE(paddr) (((uint64)paddr >> 12) << 10)
#define PTE_TO_PADDR(pte) (((uint64)pte >> 10) << 12)

#define IMAGE_START() (uint64)&_image_start
#define IMAGE_END() (uint64)&_image_end

extern uint64 _image_start;
extern uint64 _image_end;

static uint64 *kernel_pagetable = NULL;

static uint64 get_vpn(uint64 virtual_addr, uint level)
{
	switch (level) {
	case 2: return extract(virtual_addr, SV39_VPN2_OFFSET, SV39_VPN2_WIDTH);
	case 1: return extract(virtual_addr, SV39_VPN1_OFFSET, SV39_VPN1_WIDTH);
	case 0: return extract(virtual_addr, SV39_VPN0_OFFSET, SV39_VPN0_WIDTH);
	default: panic("invalid vpn level");
	}
}

Error walk(uint64 *pagetable, uint64 virtual_addr, bool alloc, void **pte)
{
	if (virtual_addr > SV39_MAX_ADDR) {
		panic("mmap addr too big");
	}

	for (uint level = 2; level > 0; level--) {
		uint64 vpn = get_vpn(virtual_addr, level);

		if (pagetable[vpn] == 0) {
			void *next;

			if (!alloc) {
				return E_NOT_EXIST;
			}

			next = kalloc_page();
			if (next == NULL) {
				return E_NOMEM;
			}

			pagetable[vpn] = PADDR_TO_PTE(next) | PTE_V;
		}

		pagetable = (uint64 *)PTE_TO_PADDR(pagetable[vpn]);
	}

	*pte = &pagetable[get_vpn(virtual_addr, 0)];
	return E_OK;
}

Error mmap_page(void *pagetable, uint64 virtual_addr, uint64 physical_addr, PagePerm perm)
{
	void *pte;
	Error err;

	if ((err = walk(pagetable, virtual_addr, true, &pte))) {
		return err;
	}

	*(uint64 *)pte = PADDR_TO_PTE(physical_addr) | perm;

	return E_OK;
}

void mmap_kernel_space(void)
{
	Error err;

	kernel_pagetable = kalloc_page();
	if (kernel_pagetable == NULL) {
		panic("failed to allocate kernel pagetable");
	}

	for (uint64 page = IMAGE_START(); page < IMAGE_END(); page += PAGE_SIZE) {
		err = mmap_page(kernel_pagetable, page, page, PAGE_PERM_KERNEL);
		panic_on(err, "failed to mmap kernel space");
	}
}

void mmu_init(void)
{
}

void mmu_enable(void)
{
	csr_set_satp((uint64)kernel_pagetable >> 12, 0, SATP_MODE_SV39);
}
