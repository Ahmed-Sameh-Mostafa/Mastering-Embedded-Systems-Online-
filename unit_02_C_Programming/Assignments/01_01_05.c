/*
 * 	File Name:01_01_05.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C Program to Find ASCII Value of a Character
 */

#include <stdio.h>

int main(void)
{
	char num= 0;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c", &num);
	printf("ASCII value of the number: %d", num);
	return 0;
}
