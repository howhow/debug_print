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
#define I2C_PRINT(level, fmt, args...) DBG_PRINT(I2C, level, fmt, ##args) 

int main(/*@ unused @*/int argc, /*@ unused @*/char *argv[])
{

    DbgConfig(TRUE, I2C, FATAL);

#ifdef _DEBUG_
    printf("Debug Mask: 0x%04X\n",gDbg_mask);
#endif

    I2C_PRINT(INFO,  "test\n");
    I2C_PRINT(DEBUG, "^g^test\n");
    I2C_PRINT(WARN,  "^y^test\n");
    I2C_PRINT(ALARM, "^y^test\n");
    I2C_PRINT(ERROR, "^r^test\n");
    I2C_PRINT(FATAL, "^r^test\n");

    return 0;
}
