/*
	Author: Ahmed Sameh
	Problem Statment: Write a program in C to print a string in reverse using a pointer
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char *ptr_str = NULL , str[100];
	int size = 0;
	printf("Enter a string: ");
	gets(str);
	size = strlen(str);
	ptr_str = str;
	ptr_str += (size - 1);
	printf("Reverse of the string: ");
	while(ptr_str != str - 1)
	{
		printf("%c", *ptr_str--);
	}
	// printf("\n%p\t%p\t", str - sizeof(str),  &(str) - 1);  just a test :)
	return 0;
}