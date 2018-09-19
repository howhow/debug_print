#include "driver.h"
#include "debug.h"

#define UART_PRINT(level, fmt, args...)  DBG_PRINT(UART, level, fmt, ##args)

static drvComm_t uartDrv;

static void uartTestStart(void);
static void uartTest(void);
static void uartTestClose(void);

int uartWrite(char *buf, UINT32 len)
{
    UART_PRINT(INFO, "Write buffer: %s\n", buf);
    UART_PRINT(INFO, "Buffer size: %d\n", len);

    uartTest();

    return 0;
}

int uartClose(void)
{
    uartDrv.drvName = NULL;
    uartDrv.drvWrite = NULL;
    uartDrv.drvClose = NULL;

    UART_PRINT(INFO, "Local driver closed\n\n");

    uartTestClose();

    return 0;
}

int UartDrvInit(drvComm_t **fd)
{
    uartDrv.drvName = (unsigned char*)"uart terminal";
    uartDrv.drvWrite = uartWrite;
    uartDrv.drvClose = uartClose;

    *fd = &uartDrv;

    uartTestStart();

    UART_PRINT(INFO, "Driver init: %s\n", uartDrv.drvName);

    return 0;
}

static void uartTestStart(void)
{
    DbgConfig(UART, FATAL);

}

static void uartTest(void)
{
    UART_PRINT(INFO,  "test\n");
    UART_PRINT(DEBUG, "^g^test\n");
    UART_PRINT(WARN,  "^y^test\n");
    UART_PRINT(ALARM, "^y^test\n");
    UART_PRINT(ERROR, "^r^test\n");
    UART_PRINT(FATAL, "^r^test\n");
    UART_PRINT(FATAL, "^x^test\n");

    DbgConfig(UART, NONE);
    UART_PRINT(INFO,  "test, should not print!\n");
    UART_PRINT(DEBUG, "^g^test, should not print!\n");
    UART_PRINT(WARN,  "^y^test, should not print!\n");
    UART_PRINT(ALARM, "^y^test, should not print!\n");
    UART_PRINT(ERROR, "^r^test, should not print!\n");
    UART_PRINT(FATAL, "^r^test, should not print!\n");

    DbgConfig(UART, INFO);
    UART_PRINT(INFO,  "test\n");
    UART_PRINT(DEBUG, "^g^test\n");
    UART_PRINT(WARN,  "^y^test\n");
    UART_PRINT(ALARM, "^y^test\n");
    UART_PRINT(ERROR, "^r^test\n");
    UART_PRINT(FATAL, "^r^test\n");

}

static void uartTestClose()
{
    DbgConfig(UART, NONE);
}

