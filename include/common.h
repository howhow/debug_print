/*	@file common.h
 *
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	2.0
 *	@Date:		19th/June/2012
 *	@Note:		At V2.0, add common typedef
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define __FUNC__ 	__FUNCTION__
#define __L__		__LINE__

#ifndef UINT8
typedef unsigned char	__UINT8;
#define UINT8	__UINT8
#endif

#ifndef UINT16
typedef unsigned short __UINT16;
#define UINT16	__UINT16
#endif

#ifndef UINT32
typedef unsigned int __UINT32;
#define UINT32	__UINT32
#endif

#ifndef UINT64
typedef unsigned long long __UINT64;
#define UINT64	__UINT64
#endif

#ifndef BOOL
typedef int __BOOL;
#define BOOL __BOOL
#define TRUE    1
#define FALSE   0
#endif

#ifdef __cplusplus
}
#endif

#endif // _COMMON_H_
