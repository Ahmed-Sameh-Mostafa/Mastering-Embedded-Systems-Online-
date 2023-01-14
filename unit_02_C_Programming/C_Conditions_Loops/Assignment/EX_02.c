/*
 * 	File Name:01_02_02.c
 *
 *  Created on: 13 Jan 2023
 *  Author: Ahmed Sameh
 *  Problem Statment: Write C program to check vowel or consonant.
 */

#include <stdio.h>

int main(void)
{
	char letter = 'a';
	printf("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c", &letter);
	switch (letter)
	{
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		{
			printf("%c is a vowel",letter);
			break;
		}
		default:
		{
			printf("%c is a consonant",letter);
		}

	}
	return 0;
}
