/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: write a c program to find length of a string
 */

#include <stdio.h>

int main(void)
{
	char str[100], length = 0;
	int i = 0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);

	while(str[i] != 0)
	{
		length++;
		i++;
	}
	printf("Length of string: %d", length);
	return 0;
}
