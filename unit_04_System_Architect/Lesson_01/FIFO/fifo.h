#ifndef _FIFO_H_
#define _FIFO_H_

#include <stdio.h>
#include <stdlib.h>

#define element_type	unsigned int

typedef struct 
{	
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;

} FIFO_Buf_t;

typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_Null
}Buffer_status;

Buffer_status	FIFO_init	(FIFO_Buf_t* fifo, element_type* buff, unsigned int buff_length);
Buffer_status	FIFO_enqueue(FIFO_Buf_t* fifo, element_type data);
Buffer_status	FIFO_dequeue(FIFO_Buf_t* fifo, element_type* data);
Buffer_status 	FIFO_print	(FIFO_Buf_t* fifo);
#endif