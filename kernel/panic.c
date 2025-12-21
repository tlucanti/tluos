
#include <kernel/attributes.h>
#include <kernel/panic.h>
#include <kernel/types.h>

#include <sys/kconsole.h>

void panic(char *message)
{
	kconsole_puts(message);
	kconsole_putc('\n');

	while (true) {}
}
