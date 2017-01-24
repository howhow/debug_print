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

UINT32 gDbg_mask;
UINT32 gDbg_level;

#define BIT_SET(pos) (1<<pos)

const char* grp_names[]={
    "init",
	"I2C",
	"SPI",
	"USIF",
	"USB",
	"max"
};
#define DBG_MAX (sizeof(grp_names) / sizeof(grp_names[0]))

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

#ifndef toupper
#define toupper(c) (((c > 0x60) && (c < 0x7B)) ? (c - 0x20) : c)
#endif

#ifndef stricmp
int stricmp(const char *s1, const char *s2)
{
	while(*s1 && *s2)
	{
		if(toupper(*s1) != toupper(*s2))
			return toupper(*s1) - toupper(*s2);

		s1++;
		s2++;
	}
	return toupper(*s1) - toupper(*s2);
}
#endif

#if 0
void Dbg_Cfg(const int debug, const char *grp)
{
	UINT32 val=0;

	if(grp != NULL)
	{
		unsigned int i;

		for(i = 0; i<DBG_MAX; i++)
		{
			if(stricmp(grp, grp_names[i]) == 0)
			{
				//found group
				val = (1<<i);
				break;
			}
		}
	}
	else
	{
		val = (UINT32)-1;
	}

	if(debug)
		gDbg_mask |= val;
	else
		gDbg_mask &= ~val;
}
#else
void Dbg_Cfg(BOOL grp_enable, dbg_grp_e grp, dbg_level_e level)
{
    UINT32 val = 0x0;

    if(grp > init_grp && grp < max_grp)
    {
        //found group
        val = (1<<grp);
    }

    if(grp_enable)
    {
        gDbg_mask |= val;
    }
    else
    {
        gDbg_mask &= ~val;
    }

    gDbg_level = level;
}
#endif

#ifdef _DEBUG_
static BOOL Dbg_IsGrpEnabled(dbg_grp_e grp)
{
	if(BIT_SET(grp) & gDbg_mask)
		return TRUE;

	return FALSE;
}

static BOOL Dbg_IsLevelEnabled(dbg_level_e level)
{
    if (level <= gDbg_level)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

static int DBGvsprint(FILE *stream, const char *format, va_list args)
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

	if(*format == '!')
		return 0;

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
	}

	count = vsnprintf(&dbgBUF[0], DBG_BUFFER_SIZE-14, format, args);
	(*pFunc)(stream, "%s%s%s", color1, dbgBUF, color2);

	return count;
}

static int va_aprintOn(FILE *stream, const char *fmt, va_list args)
{
	return DBGvsprint(stream, fmt, args);
}

int DBG_PrintColor(dbg_grp_e grp, dbg_level_e level, FILE *stream, const char *fmt, ...)
{
    int count = 0;
#ifdef _DEBUG_
    if( Dbg_IsGrpEnabled(grp) && Dbg_IsLevelEnabled(level) )
    {
        va_list args;

        va_start(args, fmt);
        count = va_aprintOn(stream, fmt, args);
        va_end(args);
    }
#endif
    return count;
}

