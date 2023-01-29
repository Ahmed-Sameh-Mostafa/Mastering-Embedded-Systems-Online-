/*
 * 		platform_Types.h
 *
 * 	 	Created on: 27 Jan 2023
 *      Author: 	Ahmed Sameh
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#ifndef boolean
#define boolean unsigned char
#endif

#define true	1
#define false	0

#ifndef FALSE
#define FALSE 	(boolean)false
#endif

#ifndef TRUE
#define TRUE	(boolean)true
#endif

typedef char sint8;
typedef unsigned char uint8;
typedef char char_t;
typedef short sint16;
typedef unsigned short uint16;
typedef long sint32;
typedef unsigned long uint32;
typedef long long sint64;
typedef unsigned long long uint64;

typedef volatile char vint8_t;
typedef volatile unsigned char vuint8_t;

typedef volatile short vint16_t;
typedef volatile unsigned short vuint16_t;

typedef volatile long vint32_t;
typedef volatile unsigned long vuint32_t;

typedef volatile long long vint64_t;
typedef volatile unsigned long long vuint64_t;

typedef float float32;
typedef double float64;


#endif /* PLATFORM_TYPES_H_ */
