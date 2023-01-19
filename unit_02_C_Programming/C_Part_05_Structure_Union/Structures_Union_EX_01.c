/*
    Author: Ahmed Sameh
    Problem Statment: C program to store information(name, roll and marks) of a student using structure
*/

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
    struct S_Student student;
    student = read_student_data();
    display_student_data(student);
    return 0;
}
struct S_Student read_student_data(void)
{
    struct S_Student student;
    printf("Enter information of students:\n\n");
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
    printf("\nDisplaying information of students:\n\n");
    printf("Name: %s\n", x.name);
    printf("Roll number: %d\n", x.roll);
    printf("Mark: %.2f\n", x.marks);
}

