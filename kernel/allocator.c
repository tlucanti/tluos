
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <container/slist.h>

#define HEAP_SIZE_PAGES 128
#define PAGE_SIZE 4096

__aligned(4096) extern uint8 heap_start[];
static bool occupied_pages[HEAP_SIZE_PAGES];

void kpage_alloc_init(void)
{
	for (uint64 i = 0; i < HEAP_SIZE_PAGES; i++) {
		occupied_pages[i] = false;
	}
}

/**
 * kpage_alloc() - allocate physical pages
 *
 * @param order: allocate 2 ^ order physical pages
 * @return: pointer to allocated memory
 */
void *kpage_alloc(uint order)
{
	const uint64 num_pages = (uint64)2 << order;
	uint64 start = 0;
	uint64 end;
	uint64 occupied = 0;
	void *ret;

	/**
	 * algorithm work as follows: we have sliding window of size @num_pages
	 * from @start to @end. And maintaining number of free pages in this
	 * window in @occupied. As soon as @occupied drops to zero - we found
	 * countonous interval of non occupied pages
	 */
	for (end = 0; end < num_pages; end++) {
		occupied += occupied_pages[end];
	}

	while (end < HEAP_SIZE_PAGES) {
		if (occupied == 0)
			goto found;
		occupied += occupied_pages[end];
		occupied -= occupied_pages[start];
		start++;
		end++;
	}

	return NULL; // no memory

found:
	ret = heap_start + start * PAGE_SIZE;
	for (; start != end; start++) {
		occupied_pages[start] = true;
	}
	return ret;
}

void kpage_free(void *page, uint order)
{
	uint64 num_pages = (uint64)2 << order;

	for (uint64 i = 0; i < num_pages; i++) {
		occupied_pages[i] = false;
	}
}

