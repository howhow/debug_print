#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "driver.h"

int localWrite(char *buf, UINT32 len);
int localClose(void);
int UartDrvInit(drvComm_t **fd);

#ifdef __cplusplus
}
#endif

#endif // _UART_H_

