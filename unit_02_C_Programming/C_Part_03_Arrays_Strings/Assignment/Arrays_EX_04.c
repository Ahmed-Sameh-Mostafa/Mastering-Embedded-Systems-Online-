/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write C program to insert element into an array
 */

#include <stdio.h>

int main(void)
{
	int arr[100] = {0}, num = 0, element = 0, location = 0, length = 0;
	printf("Enter no of elements: ");
	fflush(stdout);
	scanf("%d", &num);

	for(int i = 0; i < num; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Enter The element to be inserted: ");
	fflush(stdout);
	scanf("%d", &element);

	printf("Enter location of the element: ");
	fflush(stdout);
	scanf("%d", &location);
	length = num + 1;
	while(num >= location)
	{
		arr[num] = arr[num -1];
		num--;
	}
	arr[num] = element;
	for(int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
