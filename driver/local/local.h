#ifndef _LOCAL_H_
#define _LOCAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "driver.h"

int localWrite(char *buf, UINT32 len);
int localClose(void);
int LocalTerminalInit(drvComm_t **fd);

#ifdef __cplusplus
}
#endif

#endif // _LOCAL_H_

