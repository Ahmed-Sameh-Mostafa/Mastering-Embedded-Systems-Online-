/*
 * 	File Name:01_01_03.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C Program to Add Two Integers
 */

#include <stdio.h>

int main(void)
{
	int num1 = 0, num2 = 0;
	printf("Enter two integer numbers: ");
	fflush(stdout);
	scanf("%d",&num1);
	scanf("%d",&num2);
	printf("Sum: %d", num1 + num2);
	return 0;
}
