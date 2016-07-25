#include <linux/pid_namespace.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/quicklake.h>

#define CMD_DUMP	"dump"
#define CMD_RESTORE	"restore"

#ifdef CONFIG_QUICKLAKE_OPT_O0
#pragma GCC push_options
#pragma GCC optimize ("O0")
#endif

void ql_checkpoint(void)
{
	spin_unlock_irq(&current->sighand->siglock);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule();
}

static int ql_start_dump(struct task_struct *task)
{
	if (task->exit_state & TASK_QL)
		return -ENOEXEC;
	task->exit_state = task->exit_state | TASK_QL;
	send_sig_info(SIGSTOP, (struct siginfo *) 2, task);
	set_tsk_thread_flag(task, TIF_SIGPENDING);
	if (!wake_up_state(task, TASK_INTERRUPTIBLE)) {
		kick_process(task);
	}
	return 0;
}

static int ql_start_restore(struct task_struct *task)
{
	task->exit_state = task->exit_state & ~TASK_QL;
	if (!wake_up_state(task, TASK_UNINTERRUPTIBLE)) {
		kick_process(task);
	}
	return 0;
}

int quicklake_request(struct task_struct *task, char *buf, size_t count)
{
	if (!strncmp(buf, CMD_DUMP, sizeof(CMD_DUMP) - 1)) {
		return ql_start_dump(task);	
	} else if (!strncmp(buf, CMD_RESTORE, sizeof(CMD_RESTORE) - 1)) {
		return ql_start_restore(task);
	}
	return -EINVAL;
}

#ifdef CONFIG_QUICKLAKE_OPT_O0
#pragma GCC pop_options
#endif
