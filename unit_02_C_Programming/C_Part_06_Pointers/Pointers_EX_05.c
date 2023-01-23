/*
	Author: Ahmed Sameh
	Problem Statment: 	Write a program in C to show a pointer to an array which contents 
						are pointer to structure. 
*/
#include <stdio.h>
#define SIZE 3

struct S_employee
{
	char name[20];
	int id;
};

int main(void)
{
	struct S_employee arr[SIZE];
	printf("Enter the data of the employees: \n\n");
	for(int i = 0; i < SIZE; i++)
	{
		printf("Enter Employee's name: ");
		gets(arr[i].name);
		fflush(stdin);
		printf("Enter Employee's id: ");
		scanf("%d",&arr[i].id);
		fflush(stdin);
	}

	printf("\nprinting using array of pointers:\n");
	struct S_employee * ptr_arr[SIZE]; 
	for(int i = 0; i < SIZE; i++)
	{
		ptr_arr[i] = &arr[i];
		printf("Name: %s\tID: %d\n", ptr_arr[i]->name, ptr_arr[i]->id);
	}

	printf("\nprinting using pointer to array of pointers:\n");
	struct S_employee *(* ptr_ptr_arr)[SIZE]; 
	ptr_ptr_arr = &ptr_arr;
	for(int i = 0; i < SIZE; i++)
	{
		printf("Name: %s\tID: %d\n", (*ptr_ptr_arr)[i]->name, (*ptr_ptr_arr)[i]->id);
	}
	return 0;
}