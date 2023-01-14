/*
 * 	File Name:01_02_04.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write c program to check whether a number is positive or negative or zero.
 */

#include <stdio.h>

int main(void)
{
	float num;
	printf("Enter a number: ");
	fflush(stdout);
	scanf("%f", &num);
	if (num > 0)
		printf("%f is positive", num);
	else if (num < 0)
		printf("%f is negative", num);
	else
		printf("You entered zero");

	return 0;
}
