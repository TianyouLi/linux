#ifndef _LINUX_QUICKLAKE_H
#define _LINUX_QUICKLAKE_H

#include <linux/file.h>
#include <uapi/linux/quicklake.h>

#define QL_DUMP		0
#define QL_RESTORE	1

int quicklake_request(struct task_struct *, int cmd);
void ql_checkpoint(void);

#endif
