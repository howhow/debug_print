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
extern const char *grp_names[];
#endif

/* Example to use DBG print for each compoenet */
#define I2C_PRINT(level, fmt, args...) DBG_PRINT(I2C, level, fmt, ##args) 

int main(/*@ unused @*/int argc, /*@ unused @*/char *argv[]) //comment for lint
{

	Dbg_Cfg(TRUE, I2C, FATAL);

#ifdef _DEBUG_
    printf("Debug Mask: 0x%04X\n",gDbg_mask);
#endif

	I2C_PRINT(INFO, "[%s] test\n", grp_names[I2C]);
	I2C_PRINT(DEBUG, "^g^[%s] test\n", grp_names[I2C]);
	I2C_PRINT(WARN, "^y^[%s] test\n", grp_names[I2C]);
	I2C_PRINT(ALARM, "^y^[%s] test\n", grp_names[I2C]);
	I2C_PRINT(ERROR, "^r^[%s] test\n", grp_names[I2C]);
	I2C_PRINT(FATAL, "^r^[%s] test\n", grp_names[I2C]);
	
	return 0;
}
