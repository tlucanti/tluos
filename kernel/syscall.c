
#include <kernel/syscall.h>
#include <kernel/task.h>
#include <kernel/types.h>
#include <sys/console.h>
#include <sys/riscv.h>

#define syscall_num() current_task->trapframe.a7
#define syscall_arg(n) current_task->trapframe.a##n
#define syscall_ret() current_task->trapframe.a0

extern struct frame trapframe;

static uint sys_getcpu(void);
static void sys_print(const char *s);

void syscall(void)
{
	switch (syscall_num()) {
		break;
	case SYS_GETCPU:
		console_puts("called syscall: SYS_GETCPU\n");
		syscall_ret() = sys_getcpu();
		break;
	case SYS_PRINT:
		console_puts("called syscall: SYS_PRINT\n");
		sys_print((const char *)syscall_arg(0));
		break;
	default:
		console_puts("WARN: invalid syscall: ");
		console_putuint(syscall_num());
		console_putc('\n');
		syscall_ret() = 0;
		break;
	}
}

static uint sys_getcpu(void)
{
	return 123456;
}

static void sys_print(const char *s)
{
	console_puts(s);
}

