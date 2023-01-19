/*
    Author: Ahmed Sameh
    Problem Statment: C program Add two distances in inch-feet System using Structures
*/

#include <stdio.h>

struct S_distance
{   
    int inch;
    float feet;
};

struct S_distance add_distance(struct S_distance x, struct S_distance y);

int main(void)
{   
    struct S_distance x = {0,0.0f}, y = {0, 0.0f}, z;
    printf("Enter information of 1st distance:\n");
    printf("Enter inch: ");
    scanf("%d", &x.inch);
    printf("Enter feet: ");
    scanf("%f", &x.feet);

    printf("\nEnter information of 2nd distance:\n");
    printf("Enter inch: ");
    scanf("%d", &y.inch);
    printf("Enter feet: ");
    scanf("%f", &y.feet);

    z = add_distance(x, y);

    printf("\nsum of distances= %d' %.1f\"", z.inch, z.feet);
    
    return 0;
}

struct S_distance add_distance(struct S_distance x, struct S_distance y)
{
    struct S_distance z = {0, 0.0f};
    z.inch = x.inch + y.inch;
    z.feet = x.feet + y.feet;

    while(z.feet >= 12.0f)
    {
        z.feet -= 12.0f;
        z.inch++;
    }
    return z;
}