#include "driver.h"
#include "local.h"
#include "uart.h"

int DrvCommInit(int **fd, drv_t device)
{
    int result = -1;

    switch(device)
    {
        case local:
            result = LocalTerminalInit((drvComm_t **)fd);
            break;

        case uart:
            //result = UartDriverCommInit((drvComm_t **)fd);
            break;

        default:
            break;
    }

    return result;
}

int DrvCommWrite(int *fd, char *buf, size_t len)
{
    int result = -1;

    result = ((drvComm_t *)fd)->drvWrite(buf, len);

    return result;
}

int DrvCommClose(int *fd)
{
    int result = -1;

    result = ((drvComm_t *)fd)->drvClose();

    return result;
}

