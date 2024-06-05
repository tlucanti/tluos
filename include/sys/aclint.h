
#ifndef SYS_ACLINT_H
#define SYS_ACLINT_H

#include <kernel/types.h>

void aclint_init(void);
uint64 aclint_mtime_get(void);
void aclint_mtimecmp_set(uint64 time);

#endif /* SYS_ACLINT_H */


