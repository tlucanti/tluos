
#include "kernel/err.h"
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

void panic_on(Error err, const char *message)
{
	const char *strerr = NULL;

	switch (err) {
	case E_OK:
		return;
	case E_NOMEM:
		strerr = "out of memory";
		break;
	case E_NOT_EXIST:
		strerr = "not exists";
		break;
	default:
		strerr = "unknown error";
		break;
	}

	kconsole_puts(message);
	kconsole_puts(": ");
	kconsole_puts(strerr);
	kconsole_putc('\n');

	while (true) {}
}
