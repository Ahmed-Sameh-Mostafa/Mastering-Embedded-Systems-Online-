/*
    Author: Ahmed Sameh
    Problem Statment: C program to find area of a circle using macros
*/

#include <stdio.h>

#define PI 3.14159265
#define Area(r) ((r) * (r) * PI)

int main(void)
{   
    float r = 0;
    printf("Enter radius of the circle: ");
    scanf("%f", &r);
    printf("Area of circle = %.2f", Area(r));
    return 0;
}