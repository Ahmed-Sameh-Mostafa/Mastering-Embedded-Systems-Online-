/*
 *
 *  	Created on: 16 Jan 2023
 *      Author: Ahmed Sameh
 *      Problem statement: write c program to reverse a sentence using recursion
 */

#include <stdio.h>

void reverse(void);

int main(void)
{
	printf("Enter a sentence: ");
	fflush(stdout);
	reverse();
	return 0;
}

void reverse(void)
{
	char c;
	scanf("%c", &c);
	if(c != '\n')
	{
		reverse();
		printf("%c", c);
	}
}
