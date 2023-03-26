#include "lifo.h"

#include <stdio.h>
#include <stdlib.h>

#define lifo_01_length	5
#define lifo_02_length  5

int main(void)
{
	element_type buff1 [lifo_01_length], temp;
	unsigned char i;

	LIFO_Buf_t lifo_01, lifo_02;
	element_type* buff2 = (element_type *)malloc(sizeof(element_type) * lifo_02_length);

	if(!LIFO_init(&lifo_01, buff1, lifo_01_length))
	{
		printf("first buffer (static allocation)	pushing items:\n");
		for(i = 0; i < lifo_01_length + 3; i++)
		{
			if(!LIFO_push(&lifo_01, i))
				printf("%d, ", i);
			else
				printf("error in pushing, ");
		}
		printf("\n\nfirst buffer poping items:\n");
		for(i = 0; i < lifo_01_length + 3; i++)
		{	
			if(!LIFO_pop(&lifo_01, &temp))
				printf("%d, ",temp);
			else
				printf("error in popping, ");
		}
		printf("\n\n");
	}
	else
	{
		printf("first buffer init failed...\n");
	}
	printf("*******************************************************************\n");
	if(!LIFO_init(&lifo_02, buff2, lifo_02_length))
	{
		printf("second buffer (dynamic allocation)	pushing items:\n");
		for(i = 0; i < lifo_02_length + 2; i++)
		{
			if(!LIFO_push(&lifo_02, i))
				printf("%d, ", i);
			else
				printf("error in pushing,");
		}
		printf("\n\nsecond buffer poping items:\n");
		for(i = 0; i < lifo_02_length + 2; i++)
		{	
			if(!LIFO_pop(&lifo_02, &temp))
				printf("%d, ",temp);
			else
				printf("error in popping, ");
		}
		printf("\n");
	}
	else
	{
		printf("second buffer init failed...\n");
	}




	return 0;
}