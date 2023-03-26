#ifndef LIFO_H
#define LIFO_H

#define element_type	unsigned int

typedef struct 
{	
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;

} LIFO_Buf_t;

typedef enum {
	LIFO_no_error,
	LIFO_full,
	LIFO_not_full,
	LIFO_empty,
	LIFO_not_empty,
	LIFO_Null
}Buffer_status;

Buffer_status	LIFO_init(LIFO_Buf_t* lifo, element_type* buff, unsigned int buff_length);
Buffer_status	LIFO_push(LIFO_Buf_t* lifo, element_type data);
Buffer_status	LIFO_pop(LIFO_Buf_t* lifo, element_type* data);
#endif