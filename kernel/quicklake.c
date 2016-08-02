#include <linux/pid_namespace.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/quicklake.h>

#pragma GCC push_options
#pragma GCC optimize ("O0")

void ql_checkpoint(void)
{
	spin_unlock_irq(&current->sighand->siglock);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule();
}

static int ql_start_dump(struct task_struct *task)
{
	if (task->ql_state & TASK_QL)
		return -ENOEXEC;
	task->ql_state = task->ql_state | TASK_QL;
	send_sig_info(SIGSTOP, (struct siginfo *) 2, task);
	set_tsk_thread_flag(task, TIF_SIGPENDING);
	if (!wake_up_state(task, TASK_INTERRUPTIBLE)) {
		kick_process(task);
	}
	return 0;
}

static int ql_start_restore(struct task_struct *task)
{
	task->ql_state = task->ql_state & ~TASK_QL;
	if (!wake_up_state(task, TASK_UNINTERRUPTIBLE)) {
		kick_process(task);
	}
	return 0;
}

int quicklake_request(struct task_struct *task, int cmd)
{
	switch (cmd) {
		case QL_DUMP:
			return ql_start_dump(task);
		case QL_RESTORE:
			return ql_start_restore(task);
	}
	return -EINVAL;
}

#pragma GCC pop_options
