#ifndef _V_TYPES_H_
#define _V_TYPES_H_

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "v_errno.h"

/*--------integers-----------------*/
typedef int				V_INT;
typedef unsigned int	V_UINT;
typedef unsigned char * V_PBYTE;
typedef unsigned char * V_LPBYTE;

typedef unsigned char	V_UINT8;
typedef signed char		V_SINT8;
typedef unsigned short	V_UINT16;
typedef signed short	V_SINT16;
typedef unsigned long	V_UINT32;
typedef signed long		V_SINT32;
typedef unsigned long long	V_UINT64;
typedef signed long long	V_SINT64;
typedef void V_VOID;

/*----------floats---------------*/
typedef float V_FLOAT;
typedef double V_DOUBLE;

/*----------bools---------------*/
typedef int V_BOOL;
#define V_TRUE	1
#define V_FALSE	0

/*----------misc---------------*/
typedef signed int V_RET;
#define V_ERROR	(-1)
#define V_OK	0
#define V_REPEAT	(-2)

typedef void *V_HANDLE;
typedef char V_CHAR;
typedef V_UINT16 V_WCHAR;		

typedef V_RET (*V_FUNC)(V_UINT32);

typedef V_VOID* (*V_THREAD)(V_VOID *);

typedef struct
{
	V_SINT32 lMin;
	V_SINT32 lMax;
	V_SINT32 lDefault;
}V_RANGE;

typedef struct
{
	V_UINT32 dwNum;
	V_SINT32 *plArray;
}V_ARRAY;

typedef struct
{
	V_SINT32 x,y;
	V_UINT32 w,h;
}V_RECT;

typedef time_t V_TIME_T;

typedef struct
{
	V_UINT32 dwSec; 	
	V_UINT32 dwUsec; 	
}V_TIMEVAL;

typedef struct
{
	V_UINT16 wYear;    // 1970 ~ 2100
	V_UINT8 byMonth;   // 1 ~ 12
	V_UINT8 byDay;     // 1 ~ 31
	V_UINT8 byHour;    // 0 ~ 23
	V_UINT8 byMinute;  // 0 ~ 59
	V_UINT8 bySecond;  // 0 ~ 59
	V_UINT8 byResv;		
}V_TIME_TM;

typedef struct
{
	V_SINT32 iInteger;	
	V_UINT32 dwDecimal;	
}V_FIX_POINT_FLOAT;		

/*******************************/
/****+------------------+*******/
/****|        TAG       |*******/
/****+------------------+*******/
/****|      V_BUFFER    |*******/
/****+------------------+*******/
/*******************************/
#define V_BUFFER_TAG_SIZE		4096

typedef struct
{
	V_VOID *pucTag;			
	V_UINT8 *pucPtr;
	V_UINT8 *pucVirtPtr;	
	V_UINT32 dwSize;
	V_UINT32 dwPrivate;		
}V_BUFFER;

typedef va_list V_VA_LIST;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define V_MIN(x,y)		((x)>(y) ? (y) : (x))
#define V_MAX(x,y)		((x)>(y) ? (x) : (y))


#define ARRAY_COPY(dst,src)	do{ memcpy((dst),(src),V_MIN(sizeof((dst)),sizeof((src)))) ;} while(0)


#define SINGLETON_DECLARE(sub_system)		static V_INT singletion##sub_system = 0
#define SINGLETON_SET(sub_system)			do{ singletion##sub_system ++; }while(0)
#define SINGLETON_RESET(sub_system)			do{ singletion##sub_system = 0; }while(0)
#define SINGLETON_CHECK(sub_system)			(singletion##sub_system)


#define PADS(id,x)		V_UINT8 pad##id[x]

#define V_ALIGN(size, align) (((V_UINT32)(size) + (align) - 1) & (~((align) - 1)))


#define V_TIME_DIFF_MS(tv_new,tv_old) ((tv_new.tv_sec-tv_old.tv_sec)*1000+((tv_new.tv_usec-tv_old.tv_usec)/1000))

/*  Four-character-code (FOURCC) */
#define V_FOURCC(a,b,c,d)\
	(((V_UINT32)(a)<<0)|((V_UINT32)(b)<<8)|((V_UINT32)(c)<<16)|((V_UINT32)(d)<<24))


typedef enum
{
	USER_LEVEL_ADMIN    = -1,
	USER_LEVEL_OPERATOR = 0
}USER_ACCESS_LEVEL;

#endif

