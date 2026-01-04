
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <kernel/panic.h>

#include <sys/allocator.h>
#include <sys/kconsole.h>

#define KERNEL_MEMORY_PAGES 256

__aligned(PAGE_SIZE)
static uint8 taken_map[KERNEL_MEMORY_PAGES];

__aligned(PAGE_SIZE)
static uint8 kernel_pages[PAGE_SIZE * KERNEL_MEMORY_PAGES];

static void zero_page(void *page)
{
	uint8 *p = (uint8 *)page;

	for (int i = 0; i < PAGE_SIZE; i++) {
		p[i] = 0;
	}
}

void allocator_init(void)
{
	for (int i = 0; i < KERNEL_MEMORY_PAGES; i++) {
		taken_map[i] = 0;
	}
}

void *alloc_physical_page(void)
{
	for (int i = 0; i < KERNEL_MEMORY_PAGES; i++) {
		if (taken_map[i] == 0) {
			taken_map[i] = 1;
			void *page = &kernel_pages[PAGE_SIZE * i];

			zero_page(page);
			return page;
		}
	}

	return NULL;
}

void free_physical_page(void *page)
{
	uint64 first_page_addr, addr, page_idx;

	first_page_addr = (uint64)&kernel_pages;
	addr = (uint64)page;
	page_idx = (addr - first_page_addr) / PAGE_SIZE;

	if (page_idx > KERNEL_MEMORY_PAGES) {
		/*
		 * function was called with page, that is outside valid
		 * pages region
		 */
		panic("invalid page passed to free_physical_page");
	}
}

