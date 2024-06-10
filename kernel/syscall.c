
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
int sys_spawn(void (*task)(void));
static void sys_sched(void);

void syscall(void)
{
	switch (syscall_num()) {
		break;
	case SYS_GETCPU:
		syscall_ret() = sys_getcpu();
		break;
	case SYS_PRINT:
		sys_print((const char *)syscall_arg(0));
		break;
	case SYS_SPAWN:
		console_puts("spawning new task\n");
		syscall_ret() = sys_spawn((void *)syscall_arg(0));
		break;
	case SYS_SCHED:
		sys_sched();
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

int sys_spawn(void (*task)(void))
{
	for (int i = 0; i < USER_TASKS_MAX; i++) {
		if (tasks[i].state == TASK_STATE_NONE) {
			/* found empty slot for user task */
			tasks[i].state = TASK_STATE_SLEEPING;
			tasks[i].pc = (uint64)task;
			/* set stacj for new task, do not forget to set address of the end of stack */
			tasks[i].trapframe.sp = (uint64)current_task->user_stack + 4096;
			return 0;
		}
	}
	return 1; // could not found a slot for new task
}

static void sys_sched(void)
{
	uint task_id = ((void *)current_task - (void *)tasks) / sizeof(struct task);

	current_task->pc = csr_read_mepc(); // save pc of current task
	current_task->state = TASK_STATE_SLEEPING; // set current tast state to sleeping
	while (true) {
		task_id = (task_id + 1) % USER_TASKS_MAX;
		if (tasks[task_id].state == TASK_STATE_SLEEPING) {
			/* found next sleeping task */
			current_task = &tasks[task_id];
			csr_write_mepc(current_task->pc); // set mepc to return to userspace to new task
			current_task->state = TASK_STATE_RUNNING;
			return;
		}
	}
}

