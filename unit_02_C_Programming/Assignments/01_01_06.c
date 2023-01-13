/*
 * 	File Name:01_01_06.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write Source Code to Swap Two Numbers
 */

#include <stdio.h>

int main(void)
{
	float num1= 0, num2=0, temp= 0;
	printf("Enter The value of a: ");
	fflush(stdout);
	scanf("%f", &num1);
	printf("Enter The value of b: ");
	fflush(stdout);
	scanf("%f", &num2);
	temp = num1;
	num1 = num2;
	num2 = temp;
	printf("The value of a: %f\n", num1);
	fflush(stdout);
	printf("The value of b: %f", num2);
	fflush(stdout);
	return 0;
}
