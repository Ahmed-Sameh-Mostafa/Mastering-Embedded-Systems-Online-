/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write c program to find frequency of an element in the string
 */

#include <stdio.h>

int main(void)
{
	char str[100], element = 0, freq = 0;

	printf("Enter a string: ");
	fflush(stdout);
	gets(str);

	printf("Enter a character to find frequency: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &element);

	int i = 0;
	while(str[i] != 0)
	{
		if(str[i] == element)
		{
			freq++;
		}
		i++;
	}
	printf("frequency of %c: %d", element, freq);
	return 0;
}
