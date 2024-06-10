
#ifndef KERNEL_TASK_H
#define KERNEL_TASK_H

#include <kernel/attributes.h>
#include <kernel/types.h>

#define USER_TASKS_MAX 32

enum task_state {
	TASK_STATE_NONE,
	TASK_STATE_RUNNING,
	TASK_STATE_SLEEPING,
};

struct frame {
	uint64 ra;
	uint64 sp;
	uint64 gp;
	uint64 tp;
	uint64 t0;
	uint64 t1;
	uint64 t2;
	uint64 s0;
	uint64 s1;
	uint64 a0;
	uint64 a1;
	uint64 a2;
	uint64 a3;
	uint64 a4;
	uint64 a5;
	uint64 a6;
	uint64 a7;
	uint64 s2;
	uint64 s3;
	uint64 s4;
	uint64 s5;
	uint64 s6;
	uint64 s7;
	uint64 s8;
	uint64 s9;
	uint64 s10;
	uint64 s11;
	uint64 t3;
	uint64 t4;
	uint64 t5;
	uint64 t6;
};

struct task {
	struct frame trapframe;
	enum task_state state;
	uint64 pc;
	uint8 user_stack[4096] __aligned(16);
};

extern struct task tasks[USER_TASKS_MAX];
extern struct task *current_task;

#endif /* KERNEL_CONTEXT_H */

