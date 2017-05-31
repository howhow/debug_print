#include "driver.h"

static drvComm_t localDrv;

int localWrite(char *buf, size_t len)
{
    printf("%s\n", buf);

    return 0;
}

int localClose(void)
{
    localDrv.drvName = NULL;
    localDrv.drvWrite = NULL;
    localDrv.drvClose = NULL;

    return 0;
}

int LocalTerminalInit(drvComm_t **fd)
{
    localDrv.drvName = (unsigned char*)"local terminal";
    localDrv.drvWrite = localWrite;
    localDrv.drvClose = localClose;

    *fd = &localDrv;
    
    return 0;
}

