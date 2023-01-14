/*
 * 	File Name:01_02_03.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write c program to find the largest number among three numbers
 */

#include <stdio.h>

int main(void)
{
	float num1 = 0, num2 = 0, num3 = 0, max = 0;
	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%f", &num1);
	scanf("%f", &num2);
	max = num1 >= num2 ? num1 : num2;
	scanf("%f", &num3);
	max = max >= num3 ? max : num3;
	printf("Largest number: %f", max);
	return 0;
}
