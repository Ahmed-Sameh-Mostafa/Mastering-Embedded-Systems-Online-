/*
	Author: Ahmed Sameh
	Problem Statment: 	Write a program in C to print the elements of an array in reverse 
						order
*/

#include <stdio.h>

int main(void)
{	int arr[15] = {0}, *ptr = NULL, size = 0;
	printf("Input the number of elements to store in the array (max 15): ");
	scanf("%d", &size);
	printf("Input %d elements in the array: \n", size);
	for(int i = 0; i < size; i++)
	{
		printf("Element-%02d: ",i + 1);
		scanf("%d", (arr + i));
	}
	printf("\nElements of the array in reverse:\n");
	ptr = arr + size;
	for(int i = size - 1; i >= 0; i--)
	{
		printf("Element-%02d: %d\n", i + 1, *--ptr);
	}
	return 0;
}