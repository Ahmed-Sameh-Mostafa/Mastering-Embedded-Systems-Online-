/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: write a c program to reverse string without using library function except strlen
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100], reverse[100];
	int length = 0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);
	length = strlen(str);
	int i;
	for( i = 0; i < length; i++)
	{
		reverse[i] = str[length - i - 1];
	}
	reverse[i] = 0;
	printf("Reverse string is: %s", reverse);
	return 0;
}
