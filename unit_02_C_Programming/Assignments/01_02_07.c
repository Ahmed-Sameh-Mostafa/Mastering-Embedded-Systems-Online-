/*
 * 	File Name:01_02_07.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write c program to find factorial of a number.
 */

#include <stdio.h>

int main(void)
{
	long num = 0;
	long long fact = 1;
	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%ld", &num);
	if ( num < 0)
	{
		printf("Error!!! Factorial of negative number doesn't exist");
	}
	else
	{
		for (int i = 2; i <= num; i++)
			fact *= i;
		printf("Factorial = %lld", fact);
	}
	return 0;
}
