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

/* define a print ptr
 */
typedef void (*PRT_FUNC_PTR)(FILE *stream, const char *fmt, ...);

/* add color here
 */
static const char *clrStrings[] = {
    "\x1b[0;30m",   /* Black */
    "\x1b[0;31m",   /* Red */
    "\x1b[0;32m",   /* Green */
    "\x1b[0;33m",   /* Yellow */
    "\x1b[0;34m",   /* Blue */
    "\x1b[0;35m",   /* Purple */
    "\x1b[0;36m",   /* Cyan */
    "\x1b[0;37m",   /* Light Gray*/
    "\x1b[0m",
};

/* Init debug info
 */
dbgInfo_t gDbgInfo[] = {
    /* group_id,    dbg_level,  group_name */
    {GRP_START,     NONE,       NULL},
    {I2C,           NONE,       "I2C"},
    {SPI,           NONE,       "SPI"},
    {USIF,          NONE,       "USIF"},
    {USB,           NONE,       "USB"},
    {GRP_END,       NONE,       NULL}
};
#define DBG_INFO_SIZE (sizeof(gDbgInfo) / sizeof(gDbgInfo[0]))

void DbgConfig(dbgGrp_e grp, dbgLevel_e level)
{
    unsigned int i;

    for(i=0; i<DBG_INFO_SIZE; i++)
    {
        if(grp == gDbgInfo[i].grpId)
        {
            gDbgInfo[i].level = level;
        }
    }
}

#ifdef _DEBUG_
static BOOL DbgIsPrintEnable(dbgGrp_e grp, dbgLevel_e level)
{
    unsigned int i;

    for(i=0; i<DBG_INFO_SIZE; i++)
    {
        if((grp == gDbgInfo[i].grpId) && level <= gDbgInfo[i].level)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static int DBGvsprint(dbgGrp_e grp, FILE *stream, const char *format, va_list args)
{
    char	dbgBUF[DBG_BUFFER_SIZE];
    int		count = 0;
    static const char	*color1 = (char *)"";
    static const char	*color2 = (char *)"";

     /* Also can link to self-print function
      * eg.
      * (PRT_FUNC_PTR)my_printf;
      */
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
            if(format[1] == ' ')
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
#endif  //#ifdef _DEBUG_

int DbgPrintColor(dbgGrp_e grp, dbgLevel_e level, FILE *stream, const char *fmt, ...)
{
    int count = 0;
#ifdef _DEBUG_
    if(DbgIsPrintEnable(grp, level))
    {
        va_list args;

        va_start(args, fmt);
        count = va_aprintOn(grp, stream, fmt, args);
        va_end(args);
    }
#endif
    return count;
}

