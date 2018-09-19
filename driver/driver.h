#ifndef _DRIVER_H_
#define _DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "common.h"

typedef int (*drvWrite_t)(char *buff, UINT32 len);
typedef int (*drvClose_t)(void);

typedef struct
{
    unsigned char   *drvName;
    drvWrite_t      drvWrite;
    drvClose_t      drvClose;
}drvComm_t;

typedef enum
{
    local = 0,
    uart = 1,
    mod3,
    mod4
}drv_t;

int DrvCommInit(int **fd, drv_t device);
int DrvCommWrite(int *fd, char *buf, UINT32 len);
int DrvCommClose(int *fd);

#ifdef __cplusplus
}
#endif

#endif // _DRIVER_H_

