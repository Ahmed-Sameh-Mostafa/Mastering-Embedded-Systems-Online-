/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write C program to calcuate average using arrays
 */

#include <stdio.h>

int main(void)
{
	float nums[100] = {0};
	double average = 0;
	int arr_len = 0;
	printf("Enter the number of data: ");
	fflush(stdout);
	scanf("%d", &arr_len);
	for(int i = 0; i < arr_len; i++)
	{
		printf("%d. Enter number: ", i+1);
		fflush(stdout);
		scanf("%f", &nums[i]);
	}

	for(int i = 0; i < arr_len; i++)
	{
		average += nums[i];
	}

	average /= arr_len;
	printf("Average = %.2lf", average);
	return 0;
}
