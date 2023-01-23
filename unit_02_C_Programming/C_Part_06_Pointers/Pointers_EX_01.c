/*
	Author: Ahmed Sameh
	Problem Statment: 	Write a program in C to demonstrate how to handle the pointers 
						in the program.
*/

#include <stdio.h>

int main(void)
{
	int m = 29, *ab = NULL;
	printf("Address of m: 0x%p\n", &m);
	printf("Value of m: %d\n\n", m);

	ab = &m;
	printf("Now ab pointer is assigned with the address of m\n");
	printf("Address of pointer ab: 0x%p\n", ab);
	printf("Content of pointer ab: %d\n\n", *ab);

	m = 34;
	printf("The value of m assigned to 34 now\n");
	printf("Address of pointer ab: 0x%p\n", ab);
	printf("Content of pointer ab: %d\n\n", *ab);

	*ab = 7;
	printf("Address of m: 0x%p\n", &m);
	printf("Value of m: %d\n", m);
	return 0;
}