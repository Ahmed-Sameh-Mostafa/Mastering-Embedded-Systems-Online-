/*
 *
 *  	Created on: 16 Jan 2023
 *      Author: Ahmed Sameh
 *      Problem statement: write c program to calculate Factorial of a number using recursion
 */

#include <stdio.h>

long long factorial(long long num);

int main(void)
{
	long long num = 0, result = 0;
	printf("Enter a positive number: ");
	fflush(stdout);
	scanf("%lld",&num);
	result = factorial(num);
	printf("factorial of %lld is: %lld",num, result);
	return 0;
}

long long factorial(long long num)
{
	if(num == 0 || num == 1)
		return 1LL;
	else if (num < 0)
		return 0LL;
	return num * factorial( num - 1);
}
