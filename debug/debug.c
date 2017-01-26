/*	@file debug.c
 *	
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	3.0
 *	@Date:		9th/Jan/2017
 *	@Note:		- V2.0, add debug print color
 *	            - V3.0, add debug component	            
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "common.h"
#include "debug.h"

#define DBG_BUFFER_SIZE 1024
#define BIT_SET(pos) (1<<pos)

UINT32 gDbg_mask;
UINT32 gDbg_level;

static const char *clrStrings[] = {
    "\x1b[30m",
    "\x1b[31m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[34m",
    "\x1b[35m",
    "\x1b[36m",
    "\x1b[37m",
    "\x1b[0m",
};

dbgInfo_t gDbgInfo[] = {
    /* group_id,    group_name */
    {GRP_START,     NULL},
    {I2C,           "I2C"},
    {SPI,           "SPI"},
    {USIF,          "USIF"},
    {USB,           "USB"},
    {GRP_END,       NULL}
};

void DbgConfig(BOOL bGrpEnable, dbgGrp_e grp, dbgLevel_e level)
{
    UINT32 val = 0x0;

    if(grp > GRP_START && grp < GRP_END)
    {
        //found group
        val = (1<<grp);
    }

    if(bGrpEnable)
    {
        gDbg_mask |= val;
    }
    else
    {
        gDbg_mask &= ~val;
    }

    gDbg_level = level;
}

#ifdef _DEBUG_
static BOOL DbgIsGrpEnable(dbgGrp_e grp)
{
    if(BIT_SET(grp) & gDbg_mask)
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL DbgIsLevelEnable(dbgLevel_e level)
{
    if (level <= gDbg_level)
    {
        return TRUE;
    }

    return FALSE;
}
#endif

static int DBGvsprint(dbgGrp_e grp, FILE *stream, const char *format, va_list args)
{
    char	dbgBUF[DBG_BUFFER_SIZE];
    int		count = 0;
    static const char	*color1 = (char *)"";
    static const char	*color2 = (char *)"";

    /*
     * Also can link to self-print function
     * eg.
     * 		(PRT_FUNC_PTR)my_printf;
     */
    //PRT_FUNC_PTR pFunc = (PRT_FUNC_PTR)printf;
    PRT_FUNC_PTR pFunc = (PRT_FUNC_PTR)fprintf;

    if(*format == '!')  return 0;

    if((format[0] == '^') && (format[2] == '^'))
    {
        int colorIndex = -1;
        switch(format[1])
        {
            case 'k': colorIndex = 0; break;
            case 'r': colorIndex = 1; break;
            case 'g': colorIndex = 2; break;
            case 'y': colorIndex = 3; break;
            case 'b': colorIndex = 4; break;
            case 'p': colorIndex = 5; break;
            case 'c': colorIndex = 6; break;
            case 'a': colorIndex = 7; break;
            default:
                      colorIndex = 0; break;
        }

        if(colorIndex >= 0)
        {
            if(!(format[1] & 0x20))
            {
                colorIndex += 8;
            }
            format += 3;
            color1 = clrStrings[colorIndex];
            color2 = clrStrings[8];
        }

        count = vsnprintf(&dbgBUF[0], DBG_BUFFER_SIZE-14, format, args);
        (*pFunc)(stream, "%s[%s] %s%s", color1, gDbgInfo[grp].grpName, dbgBUF, color2);
    }
    else
    {
        count = vsnprintf(&dbgBUF[0], DBG_BUFFER_SIZE-14, format, args);
        (*pFunc)(stream, "[%s] %s", gDbgInfo[grp].grpName, dbgBUF);
    }

    return count;
}

static int va_aprintOn(dbgGrp_e grp, FILE *stream, const char *fmt, va_list args)
{
    return DBGvsprint(grp, stream, fmt, args);
}

int DbgPrintColor(dbgGrp_e grp, dbgLevel_e level, FILE *stream, const char *fmt, ...)
{
    int count = 0;
#ifdef _DEBUG_
    if( DbgIsGrpEnable(grp) && DbgIsLevelEnable(level) )
    {
        va_list args;

        va_start(args, fmt);
        count = va_aprintOn(grp, stream, fmt, args);
        va_end(args);
    }
#endif
    return count;
}

