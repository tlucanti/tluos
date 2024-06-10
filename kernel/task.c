
#include <kernel/task.h>

struct task tasks[USER_TASKS_MAX];
struct task *current_task = NULL;

