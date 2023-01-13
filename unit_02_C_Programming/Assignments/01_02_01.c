/*
 * 	File Name:01_02_01.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C Program to check whether a number is even or odd.
 */

#include <stdio.h>

int main(void)
{
	int num = 0;
	printf("Enter an integer you want to check: ");
	fflush(stdout);
	scanf("%d",&num);
	if( num % 2 == 0)
	{
		printf("%d is even", num);
	}
	else
	{
		printf("%d is odd", num);
	}
	return 0;
}
