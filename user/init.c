
#include <kernel/attributes.h>
#include <kernel/types.h>
#include <sys/console.h>

#include <user/usys.h>

static void sleep(uint64 cycles)
{
	volatile uint64 i = cycles;
	while (i > 0) {
		i--;
	}
}

__noreturn
static void task(void)
{
	print("hello from second task\n");

	while (true) {
		print("running task ...\n");
		sleep(1e8);
		sched();
	}
}

__noreturn
void init(void)
{
	print("hello from user space\n");

	spawn(task);
	while (true) {
		print("running init ...\n");
		sleep(1e8);
		sched();
	}
}
