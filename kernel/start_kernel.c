
#include <kernel/attributes.h>
#include <kernel/task.h>
#include <kernel/types.h>
#include <sys/console.h>
#include <sys/riscv.h>

__aligned(16) uint8 _kernel_stack[4096];

extern void trap_init(void);
extern void timer_init(void);
extern __noreturn void start_userspace(void);
extern int sys_spawn(void (*task)());
extern void sys_sched(void);
extern void init(void);
__noreturn void start_user(void);

__noreturn
void start_kernel(void)
{
	console_init();
	console_puts("kernel starting\n");
	trap_init();

	start_user();
}

__noreturn
void start_user(void)
{
        csr_write_mepc((uint64)init); // set return address for mret
        csr_write_mstatus_mpp(MSTATUS_MPP_M); // set previous mode to M mode for mret
        csr_write_mstatus_mpie(true); // set previous interrupt enable to true from mret

        for (int i = 0; i < USER_TASKS_MAX; i++) {
                tasks[i].state = TASK_STATE_NONE;
        }

        current_task = &tasks[0];
        sys_spawn(init); // fill task struct for init task
        current_task->state = TASK_STATE_RUNNING;

	timer_init();
        rv_mret();
}
