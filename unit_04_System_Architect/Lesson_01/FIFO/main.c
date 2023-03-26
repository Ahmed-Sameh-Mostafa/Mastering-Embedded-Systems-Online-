#include "fifo.h"

#define buffer_1_length 5
element_type buffer_1[buffer_1_length];

int main()
{
	FIFO_Buf_t fifo_1;
	element_type temp = -1;
	unsigned int i, index = 1, counter = 0;
	if(!FIFO_init(&fifo_1, buffer_1, buffer_1_length))
		printf("FIFO_init ..... success\n");


	for(i = 0; i < buffer_1_length + 10; i++)
	{
		if(i == 3)
		{	
			FIFO_dequeue(&fifo_1, &temp);
			printf("********Dequeue	--- Done********\ndata = %d\n",temp);
			printf("tail index = %d\n",fifo_1.tail - fifo_1.base);
			continue;
		}
		if(!FIFO_enqueue(&fifo_1, counter))
			printf("*****Enqueue	--- Done*****\ndata = %d\n",counter);
		else
			printf("*****Enqueue	--- Failed*****\n");
		counter++;
	}
	printf("\n\n");

	FIFO_print(&fifo_1);
	printf("\n\n");
	for(i = 0; i < 3; i++)
	{
		if(!FIFO_dequeue(&fifo_1, &temp))
			printf("*****Dequeue	--- Done*****\ndata = %d\n",temp);
		else
			printf("*****Dequeue	--- Failed*****\n");
	}
	printf("\n\n");
	FIFO_print(&fifo_1);

	return 0;
}