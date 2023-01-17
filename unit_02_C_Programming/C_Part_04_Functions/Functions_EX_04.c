/*
 *
 *  	Created on: 16 Jan 2023
 *      Author: Ahmed Sameh
 *      Problem statement: write a c program to calculate the power of a number using recursion
 */

#include <stdio.h>

long long power(long long base, long long exponent);

int main(void)
{
	long long base = 0, exponent = 0, result = 0;

	printf("Enter base number: ");
	fflush(stdout);
	scanf("%lld", &base);

	printf("Enter exponent number(positive integer): ");
	fflush(stdout);
	scanf("%lld", &exponent);

	result = power(base, exponent);
	printf("%lld^%lld= %lld", base, exponent, result);

	return 0;
}

long long power(long long base, long long exponent)
{
	if(base == 0)
		return 0LL;
	else if(base == 1)
		return 1LL;

	if(exponent == 1)
		return base;
	return base * power(base, --exponent);
}
