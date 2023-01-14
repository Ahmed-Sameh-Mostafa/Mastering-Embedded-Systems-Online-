/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write a C program to find sum of matrix of order 2x2 using multi-dimentional arrays
 * 					  where elements of matrix are entered by user.
 */

#include <stdio.h>

int main(void)
{
	float matrix1[2][2] = {0}, matrix2[2][2] = {0};
//	double matrix_sum[2][2] = {0};
	printf("Enter the elements of the 1st matrix\n");
	for(int i = 1; i <= 2; i++)
	{
		for(int j = 1; j <= 2; j++)
		{
			printf("Enter a%d%d: ",i,j);
			fflush(stdin);
			fflush(stdout);
			scanf("%f",&matrix1[i][j]);
		}
	}

	printf("Enter the elements of the 2nd matrix\n");
	for(int i = 1; i <= 2; i++)
	{
		for(int j = 1; j <= 2; j++)
		{
			printf("Enter b%d%d: ",i,j);
			fflush(stdin);
			fflush(stdout);
			scanf("%f",&matrix2[i][j]);
		}
	}

	printf("Sum Of Matrix:\n");
	for(int i = 1; i <= 2; i++)
	{
		for(int j = 1; j <= 2; j++)
		{
			printf("%.1f\t", matrix1[i][j] + matrix2[i][j]);
			fflush(stdin);
			fflush(stdout);
		}
		printf("\n");
	}


	return 0;
}
