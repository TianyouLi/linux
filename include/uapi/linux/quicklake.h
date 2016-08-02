#ifndef _UAPI_LINUX_QUICKLAKE_H
#define _UAPI_LINUX_QUICKLAKE_H

#include <linux/ioctl.h>

#define CRCMD_IOC_MAGIC 'C' + 'R'

#define CRCMD_IOC_CHKPNT _IO(CRCMD_IOC_MAGIC, 0)
#define CRCMD_IOC_RSTORE _IO(CRCMD_IOC_MAGIC, 1)

#endif
