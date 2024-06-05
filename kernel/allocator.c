
#include <kernel/types.h>

#define HEAP_SIZE_PAGES 128
#define PAGE_SIZE 4096

extern uint8 heap_start[];

static void *free_list[HEAP_SIZE_PAGES];
static uint free_list_end = 0; // points past the end of last free page

void kalloc_init(void)
{
	for (uint i = 0; i < HEAP_SIZE_PAGES; i++) {
		free_list[i] = heap_start + (i * PAGE_SIZE);
	}

	free_list_end = HEAP_SIZE_PAGES;
}

void *page_alloc(void)
{
	if (free_list_end == 0) {
		return NULL;
	}

	--free_list_end;
	return (void *)free_list[free_list_end * PAGE_SIZE];
}

void page_free(void *page)
{
	free_list[free_list_end] = page;
	free_list_end++;
}

