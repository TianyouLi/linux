#ifndef _LINUX_QUICKLAKE_H
#define _LINUX_QUICKLAKE_H

#include <linux/file.h>

int quicklake_request(struct task_struct *, char *buf, size_t count);
void ql_checkpoint(void);

#endif
