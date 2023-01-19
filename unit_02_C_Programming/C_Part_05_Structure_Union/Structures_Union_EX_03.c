/*
    Author: Ahmed Sameh
    Problem Statment: C program to add two complex numbers by passing them to a function
*/

#include <stdio.h>

struct S_complex
{
    float real;
    float imag;
};

struct S_complex add_complex(struct S_complex x, struct S_complex y);

int main(void)
{
    struct S_complex x = {0.0f, 0.0f}, y = {0.0f,0.0f}, z = {0.0f,0.0f};
    printf("For 1st complex number:\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f", &x.real);
    scanf("%f", &x.imag);

    printf("\nFor 2nd complex number:\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f", &y.real);
    scanf("%f", &y.imag);

    z = add_complex(x, y);
    printf("\nSum = %.1f%+.1fi", z.real, z.imag);
    return 0;
}

struct S_complex add_complex(struct S_complex x, struct S_complex y)
{
    struct S_complex z = {0.0f, 0.0f};
    z.real = x.real + y.real;
    z.imag = x.imag + y.imag;
    return z;
}