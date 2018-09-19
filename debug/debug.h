/**
 *  @file debug.h
 *
 *  Main start point
 *
 *  @Author:    How.Chen
 *  @Version:   1.0
 *  @Date:      25th/Jan/2017
 *  @Note:
 *              - V0.1:
 *              - init version
 *
 *              - V0.9a:
 *              - add demo structure
 *
 *              - V1.0:
 *              - split debug build
 *              - print info to stdout/err
 *              - naming convention update
 *              - group debug info together
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

/* add own debug group here
 * sync this sequence with gDbgInfo[]
 */
typedef enum
{
    GRP_START = 0x0,
    /* Support different function */
    LOCAL = 0x1,
    UART,
    MOD3,
    MOD4,

    GRP_END
}dbgGrp_e;

typedef enum
{
    NONE = 0x0,
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
    dbgGrp_e    grpId;
    dbgLevel_e  level;
    const char  *grpName;
}dbgInfo_t;


#ifdef _DEBUG_
#define STD_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, fmt, ##args)
#define ERR_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, fmt, ##args)
#define DBG_PRINT(grp, level, fmt, args...) DbgPrintColor(grp, level, fmt, ##args)

extern int DbgPrintColor(dbgGrp_e grp, dbgLevel_e level, const char *fmt, ...);
#else
#define STD_PRINT(grp, level, fmt, args...)
#define ERR_PRINT(grp, level, fmt, args...)
#define DBG_PRINT(grp, level, fmt, args...)
#endif

void DbgConfig(dbgGrp_e grp, dbgLevel_e level);

#ifdef __cplusplus
}
#endif

#endif // _DEBUG_H_

