/*
 * GPIO.c
 *
 * Created: 18/12/2023 13:27:41
 *  Author: Lenovo
 */ 
#define output	1
#define input	0

void Port_Direction(unsigned char base, unsigned char state) // base is register port
{
	if(state == output)
	{
		(*(volatile unsigned char *)(base - 1)) = 0xff; // DDR = base - 1
	}
	else
	{
		(*(volatile unsigned char *)(base - 1)) = 0x00;
	}
}

void Pin_Direction(unsigned char base, unsigned char pin,unsigned char state) // base is register port
{
	if(state == output)
	{
		(*(volatile unsigned char *)(base - 1)) |= (1 << pin); // DDR = base - 1
	}
	else
	{
		(*(volatile unsigned char *)(base - 1)) &= ~(1 << pin);
	}
}