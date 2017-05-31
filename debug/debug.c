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

#include "common.h"
#include "debug.h"
#include "driver.h"

#define DBG_BUFFER_SIZE 1024
#define BIT_SET(pos) (1<<pos)

/* define a print ptr
 */
#if 0
typedef void (*PRT_FUNC_PTR)(FILE *stream, const char *fmt, ...);
#endif

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
 * better to sync with dbgGrp_e, then
 * 1. very easy to maintain code, only add more module in gDbgInfo[]
 * 2. very simple to check which grp is enabled by which level
 * refer to DbgConfig() and DbgIsPrintEnable() improve history
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
    gDbgInfo[grp].level = level;
}

#ifdef _DEBUG_
static BOOL DbgIsPrintEnable(dbgGrp_e grp, dbgLevel_e level)
{
    return ((grp == gDbgInfo[grp].grpId) && (level <= gDbgInfo[grp].level)) ? TRUE : FALSE;
}

static int DBGvsprint(dbgGrp_e grp, FILE *stream, const char *format, va_list args)
{
    char	dbgBuf[DBG_BUFFER_SIZE];    /* use static memory */
    char	printBuf[DBG_BUFFER_SIZE];    /* use static memory */
    int		count = 0;
    static const char	*color1 = (char *)"";
    static const char	*color2 = (char *)"";

    /* Also can link to self-print function
     * eg.
     * (PRT_FUNC_PTR)my_printf;
     */
    PRT_FUNC_PTR pFunc = (PRT_FUNC_PTR)fprintf;

    if(*format == '!')  return 0;

    memset(dbgBuf, 0x0, DBG_BUFFER_SIZE);

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

        count = vsnprintf(&dbgBuf[0], DBG_BUFFER_SIZE-14, format, args);
        /* TODO:: need call general write function
         * 1. function ptr to real driver
         */
#if 0
        (*pFunc)(stream, "%s[%s] %s%s", color1, gDbgInfo[grp].grpName, dbgBuf, color2);
#else
        snprintf(printBuf, strlen(dbgBuf)+strlen(color1)+strlen(color2)+strlen(gDbgInfo[grp].grpName), "%s[%s] %s%s", color1, gDbgInfo[grp].grpName, dbgBuf, color2);

#endif
    }
    else
    {
        count = vsnprintf(&dbgBuf[0], DBG_BUFFER_SIZE-14, format, args);
        /* TODO:: need call general write function
         * 1. function ptr to real driver
         */
        (*pFunc)(stream, "[%s] %s", gDbgInfo[grp].grpName, dbgBuf);
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

    if(DbgIsPrintEnable(grp, level))
    {
        va_list args;

        va_start(args, fmt);
        count = va_aprintOn(grp, stream, fmt, args);
        va_end(args);
    }

    return count;
}
#endif  //#ifdef _DEBUG_

