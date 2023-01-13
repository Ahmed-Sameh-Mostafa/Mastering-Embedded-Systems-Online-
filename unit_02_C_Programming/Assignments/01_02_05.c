/*
 * 	File Name:01_02_05.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write c program to check whether a character is an alphabet or not.
 */

#include <stdio.h>

int main(void)
{
	char letter = 'a';
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c", &letter);
	if ((letter <= 'z' && letter >= 'a') || (letter <= 'Z' && letter >= 'A'))
		printf("%c is an alphabet", letter);
	else
		printf("%c is not an alphabet", letter);
	return 0;
}
