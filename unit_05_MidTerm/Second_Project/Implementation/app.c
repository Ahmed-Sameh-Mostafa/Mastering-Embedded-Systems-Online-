#include "student_fifo.h"

#define STUDENTS_SIZE 55

typedef enum
{
	add_manually = 1, add_file, find_by_roll, find_by_fname, find_by_course, count_students, delete_student, update_student, show_all_info, exit_app
} operations;

int main()
{
	FIFO_Buf_t students_queue;
	element_type students_buffer[STUDENTS_SIZE];
	operations choice;

	if(FIFO_init(&students_queue, students_buffer, STUDENTS_SIZE) != FIFO_no_error)
	{
		DPRINTF("[ERROR] failed in initializing the buffer\n");
	}
	else
	{
		DPRINTF("[INFO] initialized the buffer\n");
	}

	DPRINTF("Welcome to the Student Management System\n");
	while(1)
	{
		DPRINTF("Choose The Task that you want to perform\n");
		DPRINTF("1. Add The Student Details Manually\n");
		DPRINTF("2. Add The Student Details From Text File\n");
		DPRINTF("3. Find The Student Details by Roll Number\n");
		DPRINTF("4. Find The Student Details by First Name\n");
		DPRINTF("5. Find The Student Details by Course ID\n");
		DPRINTF("6. Find The Total Number of Students\n");
		DPRINTF("7. Delete The Student's Details by Roll Number\n");
		DPRINTF("8. Update The Student's Details by Roll Number\n");
		DPRINTF("9. Show All Information\n");
		DPRINTF("10. To Exit\n");
		DPRINTF("Enter Your choice to perform the Task: ");
		scanf("%d", &choice);
		DPRINTF("=========================\n");
		switch(choice)
		{
			case add_manually: 
				add_student_manually(&students_queue); 
				break;
			case add_file:
				add_student_file(&students_queue);
				break;
			case find_by_roll:
				find_r1(&students_queue);
				break;
			case find_by_fname:
				find_fn(&students_queue);
				break;
			case find_by_course:
				find_c(&students_queue);
				break;
			case count_students:
				tot_s(&students_queue);
				break;
			case delete_student:
				del_s(&students_queue);
				break;
			case update_student:
				up_s(&students_queue);
				break;
			case show_all_info:
				show_s(&students_queue);
				break;
			case exit_app:
				return 0;
			default:
				DPRINTF("[ERROR] Wrong choice, try again\n");
				break;
		}
		DPRINTF("=========================\n");

	}

	return 0;
}


