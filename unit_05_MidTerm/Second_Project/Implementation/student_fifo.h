#ifndef _FIFO_H_
#define _FIFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50
#define COURSES_SIZE 5

struct student_info 
{
	char fname[NAME_LENGTH];
	char lname[NAME_LENGTH];
	int roll;
	float GPA;
	int cid[COURSES_SIZE];
};

typedef struct student_info s_data;

typedef s_data	element_type;

typedef struct 
{	
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;

} FIFO_Buf_t;

#define DPRINTF(...)	{fflush(stdin);\
						fflush(stdout);\
						printf(__VA_ARGS__);\
						fflush(stdin);\
						fflush(stdout);}

typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_Null,
	FIFO_not_full,
	FIFO_not_empty,
}Buffer_status;

Buffer_status	FIFO_init	(FIFO_Buf_t* fifo, element_type* buff, unsigned int buff_length);
Buffer_status	FIFO_enqueue(FIFO_Buf_t* fifo, element_type data);
Buffer_status	FIFO_dequeue(FIFO_Buf_t* fifo, element_type* data);
Buffer_status 	FIFO_print	(FIFO_Buf_t* fifo);
Buffer_status 	FIFO_is_empty	(FIFO_Buf_t* fifo);
Buffer_status 	FIFO_is_full	(FIFO_Buf_t* fifo);

void add_student_file(FIFO_Buf_t* students_queue);
void add_student_manually(FIFO_Buf_t* students_queue);
void find_r1(FIFO_Buf_t* students_queue); //find the student details by roll number
void find_fn(FIFO_Buf_t* students_queue); //find the student details by first name
void find_c(FIFO_Buf_t* students_queue); //find the student details by course id
void tot_s(FIFO_Buf_t* students_queue); // find the total number of students 
void del_s(FIFO_Buf_t* students_queue); // delete the student by roll number
void up_s(FIFO_Buf_t* students_queue); // update the student by roll number
void show_s(FIFO_Buf_t* students_queue); // show all information

#endif