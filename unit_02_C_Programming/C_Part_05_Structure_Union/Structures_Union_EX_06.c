/*
    Author: Ahmed Sameh
    Problem Statment: write output of this program
*/

#include <stdio.h>
union job //defining a union
{
    char name[32]; // 32 bytes
    float salary; // 4 bytes
    int worker_no; // 4 bytes
}u;

// union is 32 bytes

struct job1 //defining a struct
{
    char name[32]; // 32 bytes
    float salary; // 4 bytes
    int worker_no; // 4 bytes
}u1;

// struct is 40 bytes 

int main(void)
{   
    float r = 0;
    printf("Size of union: %d\n", sizeof(u));
    printf("Size of struct: %d", sizeof(u1));
    return 0;
}