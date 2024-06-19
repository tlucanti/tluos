
#ifndef CONTAINER_SLIST_H
#define CONTAINER_SLIST_H

#include <kernel/util.h>

struct slist {
	struct slist *next;
};

#define for_each_slist_entry(head) for (; (head) != NULL; (head) = (head)->next)

#endif /* CONTAINER_SLIST_H */

