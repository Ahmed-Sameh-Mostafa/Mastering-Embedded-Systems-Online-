/*
 * 	File Name:01_01_02.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C Program to Print a Integer Entered by a User
 */

#include <stdio.h>

int main(void)
{
	int number = 0;
	printf("Enter an integer number: ");
	fflush(stdout);
	scanf("%d",&number);
	printf("You entered: %d", number);
	return 0;
}
