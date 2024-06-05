
#include <kernel/attributes.h>
#include <sys/console.h>

__noreturn
void init(void)
{
	console_puts("=== user ===\n");
	console_puts("hello from user space\n");

	while (true);
}
