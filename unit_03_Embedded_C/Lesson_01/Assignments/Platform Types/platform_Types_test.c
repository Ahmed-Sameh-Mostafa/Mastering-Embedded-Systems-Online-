/*
 * 	main.c
 *
 *  Created on: 28 Jan 2023
 *  Author: 	Lenovo
 */

#include <stdio.h>
#include "platform_Types.h"

int main(void)
{
	printf("Size of sint8: %lld",sizeof(sint8));  		// 1
	printf("\nSize of uint8: %lld",sizeof(uint8));		// 1
	printf("\nSize of sint16: %lld",sizeof(sint16));	// 2
	printf("\nSize of uint16: %lld",sizeof(uint16));	// 2
	printf("\nSize of sint32: %lld",sizeof(sint32));	// 4
	printf("\nSize of uint32: %lld",sizeof(uint32));	// 4
	printf("\nSize of sint64: %lld",sizeof(sint64));	// 8
	printf("\nSize of uint64: %lld",sizeof(uint64));	// 8

	printf("\n");

	printf("\nSize of vint8_t: %lld",sizeof(vint8_t));			// 1
	printf("\nSize of vuint8_t: %lld",sizeof(vuint8_t));		// 1
	printf("\nSize of vint16_t: %lld",sizeof(vint16_t));		// 2
	printf("\nSize of vuint16_t: %lld",sizeof(vuint16_t));		// 2
	printf("\nSize of vint32_t: %lld",sizeof(vint32_t));		// 4
	printf("\nSize of vuint32_t: %lld",sizeof(vuint32_t));		// 4
	printf("\nSize of vint64_t: %lld",sizeof(vint64_t));		// 8
	printf("\nSize of vuint64_t: %lld",sizeof(vuint64_t));		// 8

	printf("\n");

	printf("\nSize of float32: %lld",sizeof(float32));		// 4
	printf("\nSize of float64: %lld",sizeof(float64));		// 8
	return 0;
}
