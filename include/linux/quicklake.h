#ifndef _LINUX_QUICKLAKE_H
#define _LINUX_QUICKLAKE_H

#include <linux/file.h>
#include <uapi/linux/quicklake.h>

#define QL_DUMP		2257
#define QL_RESTORE	2261

#define TASK_QL_NONE		0
#define TASK_QL_SLEEP		1
#define TASK_QL_WAKEUP		2
#define TASK_QL_MAX			4

int quicklake_request(struct task_struct *, int cmd);
void ql_checkpoint(void);

#endif
