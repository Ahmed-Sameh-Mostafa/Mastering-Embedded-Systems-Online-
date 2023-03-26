#include "lifo.h"
#include <stdlib.h>

Buffer_status	LIFO_init(LIFO_Buf_t* lifo, element_type* buff, unsigned int buff_length)
{
	if(!lifo || !buff || (buff_length == 0))
	{
		lifo->base = NULL;
		lifo->head = NULL;
		return LIFO_Null;
	}
	lifo->count = 0;
	lifo->base = buff;
	lifo->length = buff_length;
	lifo->head = buff;
	return LIFO_no_error;
}



Buffer_status	LIFO_push(LIFO_Buf_t* lifo, element_type data)
{
	if(!lifo || !lifo->head || !lifo->base)
		return LIFO_Null;
	if(lifo->count == lifo->length)
		return LIFO_full;
	*(lifo->head) = data;
	lifo->head++;
	lifo->count++;
	return LIFO_no_error;
}



Buffer_status	LIFO_pop(LIFO_Buf_t* lifo, element_type* data)
{
	if(!lifo || !lifo->head || !lifo->base)
		return LIFO_Null;
	if(lifo->count == 0)
		return LIFO_empty;

	lifo->head--;
	*data = *(lifo->head);
	lifo->count--;
	return LIFO_no_error;
}