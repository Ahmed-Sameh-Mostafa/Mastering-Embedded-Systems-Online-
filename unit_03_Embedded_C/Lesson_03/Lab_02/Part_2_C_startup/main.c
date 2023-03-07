// created by Ahmed Sameh in Mastering embedded systems diploma

#include <main.h>

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE	+ 0X0C);
long g_array[] = {1,2,3,5,-1};
long g_unInitialized_array[5];
const char str[] = "Hello World";

extern void NMI_Handler(void)
{
	// just anything
	static nmi_variable = 1;
}

int main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	uint32 i = 0;
	while(1)
	{
		R_ODR->Pin.P_13 = 1;
		for(i = 0; i < 5000; i++);
		R_ODR->Pin.P_13 = 0;
		for(i = 0; i < 5000; i++);
	}
}