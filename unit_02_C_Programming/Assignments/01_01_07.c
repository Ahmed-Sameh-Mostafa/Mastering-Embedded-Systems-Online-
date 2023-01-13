/*
 * 	File Name:01_01_06.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write Source Code to Swap Two Numbers without temp variable.
 */

#include <stdio.h>

int main(void)
{
	float num1= 0, num2=0;
	printf("Enter The value of a: ");
	fflush(stdout);
	scanf("%f", &num1);
	printf("Enter The value of b: ");
	fflush(stdout);
	scanf("%f", &num2);
	num1 = num1 + num2; // num1 = a + b, 			num2 = b
	num2 = num1 - num2; // num1 = a + b, 			num2 = a + b - b = a
	num1 = num1 - num2; // num1 = a + b - a = b, 	num2 = a 
	printf("The value of a: %f\n", num1);
	fflush(stdout);
	printf("The value of b: %f", num2);
	fflush(stdout);
	return 0;
}
