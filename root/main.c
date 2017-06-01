/*	@file Main.c
 *
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	3.0
 *	@Date:		9th/Jan/2016
 *	@Note:		- V2.0, add thread
 *	            - V3.0, remove thread
 *	            add debug config
 *	            add debug print
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "debug.h"

#ifdef _DEBUG_
extern UINT32 gDbg_mask;
#endif

/* Example to use DBG print for each component */
#define MOD1_PRINT(level, fmt, args...)  DBG_PRINT(MOD1, level, fmt, ##args) 
#define MOD2_PRINT(level, fmt, args...)  DBG_PRINT(MOD2, level, fmt, ##args) 
#define MOD3_PRINT(level, fmt, args...)  DBG_PRINT(MOD3, level, fmt, ##args) 
#define MOD4_PRINT(level, fmt, args...)  DBG_PRINT(MOD4, level, fmt, ##args) 

int main(/*@ unused @*/int argc, /*@ unused @*/char *argv[])
{
    DbgConfig(MOD1, FATAL);
    DbgConfig(MOD2, FATAL);
    DbgConfig(MOD3, FATAL);
    DbgConfig(MOD4, FATAL);

    MOD1_PRINT(INFO,  "test\n");
    MOD1_PRINT(DEBUG, "^g^test\n");
    MOD1_PRINT(WARN,  "^y^test\n");
    MOD1_PRINT(ALARM, "^y^test\n");
    MOD1_PRINT(ERROR, "^r^test\n");
    MOD1_PRINT(FATAL, "^r^test\n");
    MOD1_PRINT(FATAL, "^x^test\n");

    MOD2_PRINT(INFO,  "test\n");
    MOD2_PRINT(DEBUG, "^b^test\n");
    MOD2_PRINT(WARN,  "^p^test\n");
    MOD2_PRINT(ALARM, "^p^test\n");
    MOD2_PRINT(ERROR, "^c^test\n");
    MOD2_PRINT(FATAL, "^c^test\n");

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

    DbgConfig(MOD1, NONE);
    DbgConfig(MOD2, NONE);
    DbgConfig(MOD3, NONE);
    DbgConfig(MOD4, NONE);

    MOD1_PRINT(INFO,  "test, should not print!\n");
    MOD1_PRINT(DEBUG, "^g^test, should not print!\n");
    MOD1_PRINT(WARN,  "^y^test, should not print!\n");
    MOD1_PRINT(ALARM, "^y^test, should not print!\n");
    MOD1_PRINT(ERROR, "^r^test, should not print!\n");
    MOD1_PRINT(FATAL, "^r^test, should not print!\n");

    DbgConfig(MOD1, INFO);
    DbgConfig(MOD2, WARN);
    DbgConfig(MOD3, DEBUG);
    DbgConfig(MOD4, FATAL);

    MOD1_PRINT(INFO,  "test\n");
    MOD1_PRINT(DEBUG, "^g^test\n");
    MOD1_PRINT(WARN,  "^y^test\n");
    MOD1_PRINT(ALARM, "^y^test\n");
    MOD1_PRINT(ERROR, "^r^test\n");
    MOD1_PRINT(FATAL, "^r^test\n");

    MOD2_PRINT(INFO,  "test\n");
    MOD2_PRINT(DEBUG, "^b^test\n");
    MOD2_PRINT(WARN,  "^p^test\n");
    MOD2_PRINT(ALARM, "^p^test\n");
    MOD2_PRINT(ERROR, "^c^test\n");
    MOD2_PRINT(FATAL, "^c^test\n");

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

    DbgConfig(MOD1, NONE);
    DbgConfig(MOD2, NONE);
    DbgConfig(MOD3, NONE);
    DbgConfig(MOD4, NONE);

    return 0;
}
