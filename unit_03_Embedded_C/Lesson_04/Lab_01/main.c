// created by Ahmed Sameh in Mastering embedded systems diploma

#include <main.h>


int main(void)
{
	volatile uint32 delay_count;
	SYSTCK_RCGC2_R = 0x00000020;
	//delay needed to wait until clk for portf is initialzied
	for(delay_count = 0; delay_count < 200; delay_count++);
	GPIO_PORTF_DIR_R |= 1<<3;
	GPIO_PORTF_DEN_R |= 1<<3;
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3;
		for(delay_count = 0; delay_count < 200000; delay_count++);
		GPIO_PORTF_DATA_R &= ~(1<<3);
		for(delay_count = 0; delay_count < 200000; delay_count++);

	}
	return 0;
}