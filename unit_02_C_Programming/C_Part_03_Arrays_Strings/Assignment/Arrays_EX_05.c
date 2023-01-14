/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write C program to search for an element in the array
 */

#include <stdio.h>

int main(void)
{
	int arr[100] = {0}, num = 0, element = 0;
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d", &num);

	for(int i = 0; i < num; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Enter The element to be searched: ");
	fflush(stdout);
	scanf("%d", &element);

	int i;
	for(i = 0; i < num; i++)
	{
		if (arr[i] == element)
		{
			printf("Number found at location = %d", i + 1);
			break;
		}
	}
	if( i == num)
	{
		printf("Element not found");
	}
	return 0;
}
