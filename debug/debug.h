/**
 *	@file debug.h
 *
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	1.0
 *	@Date:		25th/Jan/2017
 *	@Note:
 *	            - V0.1:
 *	            - init version
 *
 *	            - V0.9a:
 *	            - add demo structure
 *
 *	            - V1.0:
 *	            - split debug build
 *	            - print info to stdout/err
 *	            - naming convention update
 *	            - group debug info together
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
typedef enum
{
    GRP_START = 0x0,
    /* Support different function */
    I2C = 0x1,
    SPI,
    USIF,
    USB,

    GRP_END
}dbgGrp_e;

typedef enum
{
    /* support different level */
    INFO = 0x1,
    DEBUG,
    WARN,
    ALARM,
    ERROR,
    FATAL
}dbgLevel_e;

typedef struct
{
    dbgGrp_e   grpId;
    const char  *grpName;
}dbgInfo_t;

typedef void (*PRT_FUNC_PTR)(FILE *stream, const char *fmt, ...);

#ifdef _DEBUG_
#define STD_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, stdout, fmt, ##args)
#define ERR_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, stderr, fmt, ##args)
#define DBG_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, stderr, fmt, ##args)
#else
#define STD_PRINT(grp, level, fmt, args...)
#define ERR_PRINT(grp, level, fmt, args...)
#define DBG_PRINT(grp, level, fmt, args...)
#endif

extern int DbgPrintColor(dbgGrp_e grp, dbgLevel_e level, FILE *stream, const char *fmt, ...);

void DbgConfig(BOOL bGrpEnable, dbgGrp_e grp, dbgLevel_e level);

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H_

