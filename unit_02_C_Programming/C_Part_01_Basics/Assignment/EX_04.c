/*
 * 	File Name:01_01_04.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C Program to Multiply two Floating Point Numbers
 */

#include <stdio.h>

int main(void)
{
	float num1= 0, num2= 0;
	printf("Enter two numbers: ");
	fflush(stdout);
	scanf("%f", &num1);
	scanf("%f", &num2);
	printf("Product: %lf", num1 * num2);
	return 0;
}
