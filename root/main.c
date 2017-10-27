/*  @file Main.c
 *
 *  Main start point
 *
 *  @Author:    How.Chen
 *  @Version:   3.0
 *  @Date:      9th/Jan/2016
 *  @Note:      - V2.0, add thread
 *              - V3.0, remove thread
 *              add debug config
 *              add debug print
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "debug.h"
#include "driver.h"

#define TEST_STR1 "test local driver"
#define TEST_STR2 "test uart driver"
#define TEST_STR3 "test MOD3 driver"

/* Example to use DBG print for each component */
#define MOD3_PRINT(level, fmt, args...)  DBG_PRINT(MOD3, level, fmt, ##args)
#define MOD4_PRINT(level, fmt, args...)  DBG_PRINT(MOD4, level, fmt, ##args)

int main(/*@ unused @*/int argc, /*@ unused @*/char *argv[])
{
    int *fd_local;
    int *fd_uart;
    int *fd_mod3;
    //int *fd_mod4;

    DrvCommInit(&fd_local, local);
    DrvCommWrite(fd_local, (char *)TEST_STR1, strlen(TEST_STR1));
    DrvCommClose(fd_local);

    DrvCommInit(&fd_uart, uart);
    DrvCommWrite(fd_uart, (char *)TEST_STR2, strlen(TEST_STR2));
    DrvCommClose(fd_uart);

    DrvCommInit(&fd_mod3, MOD3);
    DrvCommWrite(fd_mod3, (char *)TEST_STR2, strlen(TEST_STR2));
    DrvCommClose(fd_mod3);

    DbgConfig(MOD3, FATAL);
    DbgConfig(MOD4, FATAL);

    MOD4_PRINT(INFO,  "test\n");
    MOD4_PRINT(DEBUG, "^a^test\n");
    MOD4_PRINT(WARN,  "^a^test\n");
    MOD4_PRINT(ALARM, "^k^test\n");
    MOD4_PRINT(ERROR, "^k^test\n");
    MOD4_PRINT(FATAL, "^k^test\n");

    MOD3_PRINT(INFO,  "^g^level: %d\n", INFO);
    MOD3_PRINT(DEBUG, "^y^level: %d\n", DEBUG);
    MOD3_PRINT(WARN,  "^r^level: %d\n", WARN);
    MOD3_PRINT(ALARM, "^b^level: %d\n", ALARM);
    MOD3_PRINT(ERROR, "^p^level: %d\n", ERROR);
    MOD3_PRINT(FATAL, "^c^level: %d\n", FATAL);

    DbgConfig(MOD3, NONE);
    DbgConfig(MOD4, NONE);

    DbgConfig(MOD3, DEBUG);
    DbgConfig(MOD4, FATAL);

    MOD4_PRINT(INFO,  "test\n");
    MOD4_PRINT(DEBUG, "^a^test\n");
    MOD4_PRINT(WARN,  "^a^test\n");
    MOD4_PRINT(ALARM, "^^test\n");
    MOD4_PRINT(ERROR, "^ ^test\n");
    MOD4_PRINT(FATAL, "^  ^test\n");
    MOD4_PRINT(FATAL, "!test\n");

    MOD3_PRINT(INFO,  "^g^level: %d\n", INFO);
    MOD3_PRINT(DEBUG, "^y^level: %d\n", DEBUG);
    MOD3_PRINT(WARN,  "^r^level: %d\n", WARN);
    MOD3_PRINT(ALARM, "^b^level: %d\n", ALARM);
    MOD3_PRINT(ERROR, "^p^level: %d\n", ERROR);
    MOD3_PRINT(FATAL, "^c^level: %d\n", FATAL);

    DbgConfig(MOD3, NONE);
    DbgConfig(MOD4, NONE);

    return 0;
}
