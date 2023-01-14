/*
 * 	File Name:01_02_08.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: make a calculator with (+, -, /, *) operations.
 */

#include <stdio.h>

int main(void)
{
	char op = 0;
	double num1 = 0, num2 = 0;
	printf("Enter operator either + or - or * or /: ");
	fflush(stdout);
	scanf("%c", &op);
	printf("Enter two operands: ");
	fflush(stdout);
	scanf("%lf", &num1);
	scanf("%lf", &num2);
	switch (op)
	{
		case '+':
			printf("%lf %c %lf = %lf", num1, op, num2, num1 + num2);
			break;
		case '-':
			printf("%lf %c %lf = %lf", num1, op, num2, num1 - num2);
			break;
		case '*':
			printf("%lf %c %lf = %lf", num1, op, num2, num1 * num2);
			break;
		case '/':
			printf("%lf %c %lf = %lf", num1, op, num2, num1 / num2);
			break;
		default:
			printf("Error!!! wrong operator");
	}
	return 0;
}
