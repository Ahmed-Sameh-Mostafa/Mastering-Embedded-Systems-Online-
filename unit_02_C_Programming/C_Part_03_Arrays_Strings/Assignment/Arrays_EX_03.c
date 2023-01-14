/*
 *
 *  Created on: 14 Jan 2023
 *  Author: Ahmed Sameh
 * 	Problem statment: Write C program to transpose a matrix
 */

#include <stdio.h>

int main(void)
{
	int matrix1[100][100] = {0}, matrix2[100][100] = {0};
	int row = 0, column = 0;
	printf("Enter rows and column of a matrix: ");
	fflush(stdout);
	scanf("%d", &row);
	scanf("%d", &column);

	//take input matrix from the user
	printf("Enter elements of the matrix:\n");
	fflush(stdout);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			printf("Enter element a%d%d: ", i+1, j+1);
			fflush(stdout);
			scanf("%d", &matrix1[i][j]);
		}
	}

	//display entered matrix
	printf("Entered matrix:\n");
	fflush(stdout);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			printf("%d\t", matrix1[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}

	//transpose the matrix
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			matrix2[j][i] = matrix1[i][j];
		}
	}

	//display transposed matrix
	printf("Transpose of the matrix:\n");
	fflush(stdout);
	for(int i = 0; i < column; i++)
	{
		for(int j = 0; j < row; j++)
		{
			printf("%d\t", matrix2[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}
