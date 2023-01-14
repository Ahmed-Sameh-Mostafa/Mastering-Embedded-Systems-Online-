/*
 * 	File Name:01_02_06.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write Source Code to calculate sum of natural numbers.
 */

#include <stdio.h>

int main(void)
{
	int num= 0, sum=0;
	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
		sum += i;
	printf("Sum = %d", sum);
	return 0;
}
