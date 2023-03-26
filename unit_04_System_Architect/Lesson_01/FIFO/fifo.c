#include "fifo.h"



Buffer_status	FIFO_init	(FIFO_Buf_t* fifo, element_type* buff, unsigned int buff_length)
{
	if(!fifo || !buff || !buff_length)
	{
		fifo->base = NULL;
		fifo->head = NULL;
		fifo->tail = NULL;
		return FIFO_Null;
	}
	fifo->count = 0;
	fifo->base = buff;
	fifo->length = buff_length;
	fifo->head = buff;
	fifo->tail = buff;
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


