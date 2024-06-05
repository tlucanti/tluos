
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/console.h>

#include <user/usys.h>

__noreturn
void init(void)
{
	console_puts("=== user ===\n");
	console_puts("hello from user space\n");

	uint cpu = getcpu();
	console_puts("current cpu: ");
	console_putuint(cpu);
	console_putc('\n');

	print(">> this string is written by syscall <<\n");

	while (true);
}
