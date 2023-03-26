#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DPRINTF(...)	{fflush(stdin);\
						fflush(stdout);\
						printf(__VA_ARGS__);\
						fflush(stdin);\
						fflush(stdout);}

typedef struct
{
	int ID;
	char name[40];
	float height;
}Sdata;

typedef struct Sstudent
{
	Sdata Student;
	struct Sstudent* PNextStudent;

}Sstudent;

Sstudent* gpFirstStudent = NULL;

void fill_the_record(Sstudent* new_student)
{
	char temp_text[40];

	DPRINTF("\n Enter the student's ID: ");
	gets(temp_text);
	new_student->Student.ID = atoi(temp_text);

	DPRINTF("\n Enter the student's full name: ");
	gets(new_student->Student.name);

	DPRINTF("\n Enter the student's height: ");
	gets(temp_text);
	new_student->Student.height = atof(temp_text);
}

void AddStudent()
{
	Sstudent *pLastStudent, *pNewStudent;

	if(gpFirstStudent == NULL)
	{
		pNewStudent = (Sstudent *) malloc(sizeof(Sstudent));

		gpFirstStudent = pNewStudent;
	}
	else
	{
		pLastStudent = gpFirstStudent;
		while(pLastStudent->PNextStudent)
			pLastStudent = pLastStudent->PNextStudent;

		pNewStudent = (Sstudent *) malloc(sizeof(Sstudent));

		pLastStudent->PNextStudent = pNewStudent;

	}

	fill_the_record(pNewStudent);

	pNewStudent->PNextStudent = NULL;
}

int DeleteStudent()
{
	char temp_text[40];
	int i, selected_id;

	DPRINTF("\n Enter The ID of the Student you want to deleted: ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if(gpFirstStudent)
	{
		Sstudent *pSelectedStudent = gpFirstStudent, *pPreviousStudent = NULL;
		while(pSelectedStudent)
		{
			if(pSelectedStudent->Student.ID == selected_id)
			{
				if(pPreviousStudent)
				{
					pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
				}
				else
				{
					gpFirstStudent = pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);
				return 1;
			}

			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;
		}

	}

	DPRINTF("\nDidn't find the student with ID you entered\n");
	return 0;
}

void viewStudents()
{
	int count = 0;
	Sstudent* pCurrentStudent = gpFirstStudent;
	if(gpFirstStudent == NULL)
		DPRINTF("\nEmpty list\n");

	while(pCurrentStudent)
	{
		DPRINTF("\nRecord Number %d", count + 1);
		DPRINTF("\nID: %d", pCurrentStudent->Student.ID);
		DPRINTF("\nFull Name: %s", pCurrentStudent->Student.name);
		DPRINTF("\nHeight: %f\n",pCurrentStudent->Student.height);
		pCurrentStudent = pCurrentStudent->PNextStudent;
		count++;
	}
}


void DeleteAll()
{
	Sstudent* pCurrentStudent = gpFirstStudent;
	if(gpFirstStudent == NULL)
		DPRINTF("\nEmpty list\n");

	while(pCurrentStudent)
	{
		Sstudent* pTempStudent = pCurrentStudent;
		pCurrentStudent = pCurrentStudent->PNextStudent;
		free(pTempStudent);
	}
	gpFirstStudent = NULL;
}


void ReverseList()
{
	Sstudent* pNextStudent = NULL, *pCurrentStudent = gpFirstStudent, *pPreviousStudent = NULL;

	if(gpFirstStudent == NULL)
	{
		DPRINTF("\nEmpty list\n");
		return ;
	}

	while(pCurrentStudent)
	{
		pNextStudent = pCurrentStudent->PNextStudent;
		pCurrentStudent->PNextStudent = pPreviousStudent;
		pPreviousStudent = pCurrentStudent;
		pCurrentStudent = pNextStudent;
	}

	gpFirstStudent = pPreviousStudent;

}

void GetNNodeFromEnd()
{
	char temp_text[40];
	int N = 0, count = 0;
	Sstudent* pNStudent = NULL, *pCurrentStudent = gpFirstStudent;

	if(gpFirstStudent == NULL)
	{
		DPRINTF("\nEmpty list\n");
		return ;
	}

	DPRINTF("\nEnter The number of the Node from the End you want to get: ");
	gets(temp_text);
	N = atoi(temp_text);
	while(pCurrentStudent)
	{
		if(count < N)
			count++;
		else if (count == N)
		{
			count++;
			pNStudent = gpFirstStudent;
		}
		else
			pNStudent = pNStudent->PNextStudent;
		pCurrentStudent = pCurrentStudent->PNextStudent;
	}

	if(pNStudent)
	{
		DPRINTF("\nID: %d", pNStudent->Student.ID);
		DPRINTF("\nFull Name: %s", pNStudent->Student.name);
		DPRINTF("\nHeight: %f\n",pNStudent->Student.height);
	}
	else
		DPRINTF("\nNot Found\n");

}

void FindMiddleStudent()
{
	Sstudent* pSlow = gpFirstStudent, *pFast = gpFirstStudent;

	if(gpFirstStudent == NULL)
	{
		DPRINTF("\nEmpty list\n");
		return ;
	}
	while(pSlow && pFast && pFast->PNextStudent)
	{
		pSlow = pSlow->PNextStudent;
		pFast = pFast->PNextStudent->PNextStudent;
	}
	DPRINTF("\nID: %d", pSlow->Student.ID);
	DPRINTF("\nFull Name: %s", pSlow->Student.name);
	DPRINTF("\nHeight: %f\n",pSlow->Student.height);
}

void main(void)
{

	char temp_text[40];

	while(1)
	{
		DPRINTF("\n====================================");
		DPRINTF("\n\tChoose one of the following options:\n");
		DPRINTF("\n1: AddStudent");
		DPRINTF("\n2: DeleteStudent");
		DPRINTF("\n3: viewStudents");
		DPRINTF("\n4: DeleteAll");
		DPRINTF("\n5: ReverseList");
		DPRINTF("\n6: GetNNodeFromEnd");
		DPRINTF("\n7: FindMiddleStudent");
		DPRINTF("\n8: Exit");
		DPRINTF("\nEnter Option Number: ");

		gets(temp_text);
		DPRINTF("\n====================================");

		switch(atoi(temp_text))
		{
			case 1:
				AddStudent();
				break;
			case 2:
				DeleteStudent();
				break;
			case 3:
				viewStudents();
				break;
			case 4:
				DeleteAll();
				break;
			case 5:
				ReverseList();
				break;
			case 6:
				GetNNodeFromEnd();
				break;
			case 7:
				FindMiddleStudent();
				break;
			case 8:
				return;
			default:
				DPRINTF("\nWrong option");
				break;
		}
	}
}