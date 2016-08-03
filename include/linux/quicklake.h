#ifndef _LINUX_QUICKLAKE_H
#define _LINUX_QUICKLAKE_H

#include <linux/file.h>

#define QL_DUMP		2257
#define QL_RESTORE	2261

int quicklake_request(struct task_struct *, int cmd);
void ql_checkpoint(void);

#endif
