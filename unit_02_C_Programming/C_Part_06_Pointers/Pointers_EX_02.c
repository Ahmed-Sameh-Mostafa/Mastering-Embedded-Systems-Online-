/*
	Author: Ahmed Sameh
	Problem Statment: 	Write a program in C to print all the alphabets using a pointer. Go 
						to the editor
*/

#include <stdio.h>

int main(void)
{
	char* ptr_letter = NULL, letter = 'A';
	ptr_letter = &letter;
	for(int i = 0; i < 26; i++)
	{
		printf("%c\t", (*ptr_letter)++); // ++ has same precednce as * but associtivity from right to left 
	}

	return 0;
}