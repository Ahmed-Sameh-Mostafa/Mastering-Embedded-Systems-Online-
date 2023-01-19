/*
    Author: Ahmed Sameh
    Problem Statment: C program to store infromation of students using structure
*/
#include <stdio.h>

#include <stdio.h>
#include <string.h>

struct S_Student
{
    char name[30];
    int roll;
    float marks;
};
struct S_Student read_student_data(void);
void display_student_data(struct S_Student x);
int main(void)
{   
    struct S_Student students[10];
    printf("Enter information of students:\n\n");
    for(int i = 0; i < 10; i++)
    {
        fflush(stdin);
        students[i] = read_student_data();
        printf("\n");
    }
    
    printf("\nDisplaying information of students:\n\n");
    for(int i = 0; i < 10; i++)
    {
        display_student_data(students[i]);
        printf("\n");
    }
    return 0;
}
struct S_Student read_student_data(void)
{
    struct S_Student student;
    
    printf("Enter Name: ");
    gets(student.name);
    printf("Enter roll number: ");
    scanf("%d", &student.roll);
    printf("Enter mark: ");
    scanf("%f", &student.marks);
    return student;

}
void display_student_data(struct S_Student x)
{
    
    printf("Name: %s\n", x.name);
    printf("Roll number: %d\n", x.roll);
    printf("Mark: %.2f\n", x.marks);
}