#include "uart.h"
unsigned char string_buffer[100] = "learn-in-depth:Ahmed Sameh";
unsigned char const string_buffer2[100] = "const global variable in .rodata section";
void main(void)
{
	Uart_Send_string(string_buffer);
}