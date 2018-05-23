#include "driver.h"
#include "debug.h"

#define LOCAL_PRINT(level, fmt, args...)  DBG_PRINT(LOCAL, level, fmt, ##args)

static drvComm_t localDrv;

static void localTestStart(void);
static void localTest(void);
static void localTestClose(void);

int localWrite(char *buf, size_t len)
{
    LOCAL_PRINT(INFO, "Write buffer: %s\n", buf);
    LOCAL_PRINT(INFO, "Buffer size: %d\n", len);

    localTest();

    return 0;
}

int localClose(void)
{
    localDrv.drvName = NULL;
    localDrv.drvWrite = NULL;
    localDrv.drvClose = NULL;

    LOCAL_PRINT(INFO, "Local driver closed\n\n");

    localTestClose();

    return 0;
}

int LocalTerminalInit(drvComm_t **fd)
{
    localDrv.drvName = (unsigned char*)"local terminal";
    localDrv.drvWrite = localWrite;
    localDrv.drvClose = localClose;

    *fd = &localDrv;

    localTestStart();

    LOCAL_PRINT(INFO, "Driver init: %s\n", localDrv.drvName);

    return 0;
}

static void localTestStart(void)
{
    DbgConfig(LOCAL, FATAL);

}

static void localTest(void)
{
    LOCAL_PRINT(INFO,  "test\n");
    LOCAL_PRINT(DEBUG, "^g^test\n");
    LOCAL_PRINT(WARN,  "^y^test\n");
    LOCAL_PRINT(ALARM, "^y^test\n");
    LOCAL_PRINT(ERROR, "^r^test\n");
    LOCAL_PRINT(FATAL, "^r^test\n");
    LOCAL_PRINT(FATAL, "^x^test\n");

    DbgConfig(LOCAL, NONE);
    LOCAL_PRINT(INFO,  "test, should not print!\n");
    LOCAL_PRINT(DEBUG, "^g^test, should not print!\n");
    LOCAL_PRINT(WARN,  "^y^test, should not print!\n");
    LOCAL_PRINT(ALARM, "^y^test, should not print!\n");
    LOCAL_PRINT(ERROR, "^r^test, should not print!\n");
    LOCAL_PRINT(FATAL, "^r^test, should not print!\n");

    DbgConfig(LOCAL, INFO);
    LOCAL_PRINT(INFO,  "test\n");
    LOCAL_PRINT(DEBUG, "^g^test\n");
    LOCAL_PRINT(WARN,  "^y^test\n");
    LOCAL_PRINT(ALARM, "^y^test\n");
    LOCAL_PRINT(ERROR, "^r^test\n");
    LOCAL_PRINT(FATAL, "^r^test\n");

}

static void localTestClose()
{
    DbgConfig(LOCAL, NONE);
}

