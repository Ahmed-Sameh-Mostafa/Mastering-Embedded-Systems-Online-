#include "student_fifo.h"

Buffer_status	FIFO_init	(FIFO_Buf_t* fifo, element_type* buff, unsigned int buff_length)
{
	if(!fifo || !buff || !buff_length)
	{
		fifo->base = NULL;
		fifo->head = NULL;
		fifo->tail = NULL;
		DPRINTF("[ERROR] couldn't initialize the queue");
		return FIFO_Null;
	}
	fifo->count = 0;
	fifo->base = buff;
	fifo->length = buff_length;
	fifo->head = buff;
	fifo->tail = buff;

	DPRINTF("[INFO] initialized the queue successfully");
	return FIFO_no_error;
}

Buffer_status	FIFO_enqueue(FIFO_Buf_t* fifo, element_type data)
{
	if(!fifo || !fifo->head || !fifo->tail)
		return FIFO_Null;
	if(fifo->length == fifo->count)
		return FIFO_full;

	*(fifo->head) = data; 
	fifo->count++;
	if(fifo->head == fifo->base + fifo->length -1)
	{
		printf("--------------circling----------------\n");
		fifo->head = fifo->base;
	}
	else
		fifo->head++;
	return FIFO_no_error;
}

Buffer_status	FIFO_dequeue(FIFO_Buf_t* fifo, element_type* data)
{
	if(!fifo || !fifo->head || !fifo->tail)
		return FIFO_Null;
	if(!fifo->count)
		return FIFO_empty;

	*data = *(fifo->tail);
	fifo->count--;

	if(fifo->tail == (fifo->base + fifo->length - 1))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_no_error;
}

Buffer_status FIFO_print	(FIFO_Buf_t* fifo)
{
	element_type *temp;
	int i;

	if(!fifo->count)
		return	FIFO_empty;
	temp = fifo->tail;
	printf("\n\n*********************	FIFO_print	*********************\n");
	for(i = 0; i < fifo->count; i++)
	{
		printf("index = %d, data = %d\n", temp - fifo->base,*temp);
		if(temp == fifo->base + fifo->length -1 )
			temp = fifo->base;
		else
			temp++;
	}
	
	printf("\n************************ finished printing ************************\n");
	return FIFO_no_error;
}

Buffer_status 	FIFO_is_empty	(FIFO_Buf_t* fifo)
{
	if(!fifo || !fifo->head || !fifo->tail || !fifo->base)
		return FIFO_Null;
	if(!fifo->count)
		return	FIFO_empty;

	return FIFO_not_empty;
}

Buffer_status 	FIFO_is_full	(FIFO_Buf_t* fifo)
{
	if(!fifo || !fifo->head || !fifo->tail || !fifo->base)
		return FIFO_Null;
	if(fifo->length == fifo->count)
		return FIFO_full;

	return FIFO_not_full;
}

static element_type* search_queue(FIFO_Buf_t* students_queue, int roll)
{
	int i = 0;
	element_type* current_student = students_queue->tail;

	if(FIFO_is_empty(students_queue) != FIFO_not_empty)
		return NULL;

	for(; i < students_queue->count; i++)
	{
		if(current_student->roll == roll)
			return current_student;
		if(current_student == students_queue->base + students_queue->length -1)
		{
			current_student = students_queue->base;
		}
		else
		{
			current_student++;
		}
	}
	
	return NULL;
}

static void print_info(FIFO_Buf_t* students_queue)
{
	DPRINTF("[INFO] The total number of students is: %d\n", students_queue->count);
	DPRINTF("[INFO] You can add up to %d students\n", students_queue->length);
	DPRINTF("[INFO] You can add %d more students\n", students_queue->length - students_queue->count);
	DPRINTF("-------------------------\n");
}

static void print_student(element_type* student, int show_roll)
{
	int i =0;
	DPRINTF("The student's details are:\n");
	DPRINTF("The First Name is %s\n",student->fname);
	DPRINTF("The Last Name is %s\n",student->lname);
	if(show_roll == 1)
	{
		DPRINTF("The Roll Number is %d\n",student->roll);
	}
	DPRINTF("The GPA is %.2f\n",student->GPA);
	DPRINTF("The course ID of each course\n");
	for(i = 0; i < COURSES_SIZE; i++)
	{
		DPRINTF("The ID of Course %d ID is: %d\n",i+1, student->cid[i]);
	}
	DPRINTF("-------------------------\n");
}

void add_student_file(FIFO_Buf_t* students_queue)
{
	FILE* students_txt;
	int i;
	element_type new_student;
	element_type* search_student;

	students_txt = fopen("students_data.txt","r");

	if(students_txt == NULL)
	{
		DPRINTF("[ERROR] Failed to find or open file\n");
		DPRINTF("-------------------------\n");
		return;
	}

	while(!feof(students_txt))
	{
		fscanf(students_txt, "%d", &new_student.roll);
		fscanf(students_txt, "%s", new_student.fname);
		fscanf(students_txt, "%s", new_student.lname);
		fscanf(students_txt, "%f", &new_student.GPA);
		for(i = 0; i < COURSES_SIZE; i++)
		{
			fscanf(students_txt, "%d", &new_student.cid[i]);
		}

		search_student = search_queue(students_queue, new_student.roll);
		if(search_student == NULL)
		{
			FIFO_enqueue(students_queue, new_student);
			DPRINTF("[INFO] Roll Number %d saved successfully\n", new_student.roll);
		}
		else
		{
			DPRINTF("[ERROR] Roll Number %d is already taken\n", new_student.roll);
		}

	}
	DPRINTF("[INFO] Students Details is added Successfully\n");
	DPRINTF("-------------------------\n");
	print_info(students_queue);
}

void add_student_manually(FIFO_Buf_t* students_queue)
{
	element_type new_student;
	int i;
	DPRINTF("Add The Student's Details\n");
	DPRINTF("-------------------------\n");
	DPRINTF("Enter the Roll Number: ");
	scanf("%d", &new_student.roll);
	DPRINTF("Enter the first name of the student: ");
	scanf("%s", new_student.fname);
	DPRINTF("Enter the last name of the student: ");
	scanf("%s", new_student.lname);
	DPRINTF("Enter The GPA of the student: ");
	scanf("%f", &new_student.GPA);

	DPRINTF("Enter the course ID of each course\n");
	for(i = 0; i < COURSES_SIZE; i++)
	{
		DPRINTF("Course %d ID is: ",i+1);
		scanf("%d", &new_student.cid[i]);
	}
	DPRINTF("-------------------------\n");

	if(search_queue(students_queue, new_student.roll) == NULL)
	{
		if(FIFO_enqueue(students_queue, new_student)== FIFO_no_error)
		{
			DPRINTF("[INFO] Added Student successfully\n");
			DPRINTF("-------------------------\n");
		}
		else
		{
			DPRINTF("[ERROR] Failed to Add Student\n");
			DPRINTF("-------------------------\n");
		}
	}
	else
	{
		DPRINTF("[ERROR] Failed to Add Student\n");
		DPRINTF("-------------------------\n");
	}
	print_info(students_queue);
}

void find_r1(FIFO_Buf_t* students_queue) //find the student details by roll number
{
	int roll;
	element_type* student;
	DPRINTF("Enter the Roll Number of the student: ");
	scanf("%d", &roll);
	student = search_queue(students_queue, roll);
	if(student != NULL)
	{
		print_student(student, 0);
	}
	else
	{
		DPRINTF("[ERROR] Roll number %d is not found\n", roll);
		DPRINTF("-------------------------\n");
	}

}

void find_fn(FIFO_Buf_t* students_queue) //find the student details by first name
{
	int i = 0, name_flag = 0;
	element_type* current_student = students_queue->tail;
	char fname[NAME_LENGTH];

	DPRINTF("Enter the first name of the student: ");
	scanf("%s", fname);

	if(FIFO_is_empty(students_queue) != FIFO_not_empty)
	{
		DPRINTF("[ERROR] First name %s not found\n",fname);
		DPRINTF("-------------------------\n");
		return;
	}

	for(; i < students_queue->count; i++)
	{
		if(!strcmp(fname, current_student->fname))
		{
			print_student(current_student, 1);
			name_flag++;
		}
		if(current_student == students_queue->base + students_queue->length -1)
		{
			current_student = students_queue->base;
		}
		else
		{
			current_student++;
		}
	}

	if(name_flag == 0)
	{
		DPRINTF("[ERROR] First name %s not found\n",fname);
		DPRINTF("-------------------------\n");
	}

}

void find_c(FIFO_Buf_t* students_queue) //find the student details by course id
{
	int i = 0, course_flag = 0, j =0;
	element_type* current_student = students_queue->tail;
	int cid;

	DPRINTF("Enter The course ID: ");
	scanf("%d", &cid);

	if(FIFO_is_empty(students_queue) != FIFO_not_empty)
	{
		DPRINTF("[ERROR] course ID %d not found\n",cid);
		DPRINTF("-------------------------\n");
		return;
	}

	for(; i < students_queue->count; i++)
	{
		for(j = 0; j < COURSES_SIZE; j++)
		{
			if(cid == current_student->cid[j])
			{
				print_student(current_student, 1);
				course_flag++;
				break;
			}
		}
		
		if(current_student == students_queue->base + students_queue->length -1)
		{
			current_student = students_queue->base;
		}
		else
		{
			current_student++;
		}
	}

	if(course_flag == 0)
	{
		DPRINTF("[ERROR] course ID %d not found\n",cid);
		DPRINTF("-------------------------\n");
	}
}

void tot_s(FIFO_Buf_t* students_queue) // find the total number of students 
{
	print_info(students_queue);
}

void del_s(FIFO_Buf_t* students_queue) // delete the student by roll number
{
	int i = 0, roll;
	element_type* student;
	DPRINTF("Enter the Roll Number which you want to delete: ");
	scanf("%d", &roll);
	if(FIFO_is_empty(students_queue) != FIFO_not_empty)
	{
		DPRINTF("[ERROR] Empty list\n");
		DPRINTF("-------------------------\n");
		return;
	}

	student = search_queue(students_queue, roll);

	if(student == NULL)
	{
		DPRINTF("[ERROR] This Roll number %d is not found\n", roll);
		DPRINTF("-------------------------\n");
		return;
	}

	*student = *(students_queue->tail);

	students_queue->count--;

	if(students_queue->tail == (students_queue->base + students_queue->length - 1))
		students_queue->tail = students_queue->base;
	else
		students_queue->tail++;

	DPRINTF("[INFO] The Roll number was removed successfully\n");
	DPRINTF("-------------------------\n");

}

void up_s(FIFO_Buf_t* students_queue) // update the student by roll number
{
	element_type* student;
	int roll, option = 0, i = 0;
	DPRINTF("Enter the roll number to update the entry: ");
	scanf("%d", &roll);

	student = search_queue(students_queue, roll);
	if(student == NULL)
	{
		DPRINTF("[ERROR] couldn't find the student");
		DPRINTF("-------------------------\n");
		return;
	}

	DPRINTF("1. first name\n");
	DPRINTF("2. last name\n");
	DPRINTF("3. roll number\n");
	DPRINTF("4. GPA\n");
	DPRINTF("5. courses\n");

	scanf("%d", &option);

	if(option == 1)
	{
		DPRINTF("Enter the new first name: ");
		scanf("%s", student->fname);

	}
	else if(option == 2)
	{
		DPRINTF("Enter the new last name: ");
		scanf("%s", student->lname);
	}
	else if(option == 3)
	{
		DPRINTF("Enter the new roll number: ");
		scanf("%d", &roll);
		if(search_queue(students_queue, roll) != NULL)
		{
			DPRINTF("[ERROR] the new roll number already exists\n");
			DPRINTF("-------------------------\n");
			return;
		}
		student->roll = roll;

	}
	else if(option == 4)
	{
		DPRINTF("Enter the new GPA: ");
		scanf("%f", &student->GPA);
	}
	else if(option == 5)
	{
		DPRINTF("Enter the new Courses' IDs: ");
		
		for(i = 0; i < COURSES_SIZE; i++)
		{
			scanf("%d", &student->cid[i]);
		}
	}
	else
	{
		DPRINTF("[ERROR] Wrong option, try again later\n");
		DPRINTF("-------------------------\n");
		return;
	}

	DPRINTF("[INFO] UPDATED SUCCESSFULLY.\n");
	DPRINTF("-------------------------\n");
}

void show_s(FIFO_Buf_t* students_queue) // show all information
{
	int i = 0;
	element_type* current_student = students_queue->tail;

	if(FIFO_is_empty(students_queue) != FIFO_not_empty)
	{
		DPRINTF("[ERROR] Empty list\n");
		DPRINTF("-------------------------\n");
		return;
	}

	for(; i < students_queue->count; i++)
	{
		print_student(current_student, 1);

		if(current_student == students_queue->base + students_queue->length -1)
		{
			current_student = students_queue->base;
		}
		else
		{
			current_student++;
		}
	}
}


