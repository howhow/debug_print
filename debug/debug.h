/*	@file debug.h
 *	
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	3.0
 *	@Date:		9th/Jan/2016
 *	@Note:		- V2.0, add demo structure
 *	            - V3.0, split debug build
 *	            - print info to stdout/err
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

/* add own debug group here
 */
typedef enum {
	init_grp = 0x0,
    /* Support different function */
	I2C,
	SPI,
	USIF,
	USB,

	max_grp = 0xFFFF
}dbg_grp_e;

typedef enum {
    /* support different level */
    INFO = 0x1,
    DEBUG,
    WARN,
    ALARM,
    ERROR,
    FATAL
}dbg_level_e;


typedef void (*PRT_FUNC_PTR)(FILE *stream, const char *fmt, ...);

#ifdef _DEBUG_
#define STD_PRINT(grp, level, fmt, args...) DBG_PrintColor(grp, level, stdout, fmt, ##args)
#define ERR_PRINT(grp, level, fmt, args...) DBG_PrintColor(grp, level, stderr, fmt, ##args)
#define DBG_PRINT(grp, level, fmt, args...) DBG_PrintColor(grp, level, stderr, fmt, ##args)
#else
#define STD_PRINT(grp, level, fmt, args...)
#define ERR_PRINT(grp, level, fmt, args...)
#define DBG_PRINT(grp, level, fmt, args...)
#endif

extern int DBG_PrintColor(dbg_grp_e grp, dbg_level_e level, FILE *stream, const char *fmt, ...);

void Dbg_Cfg(BOOL grp_enable, dbg_grp_e grp, dbg_level_e level);

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H_

