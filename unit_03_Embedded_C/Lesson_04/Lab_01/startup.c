// created by Ahmed Sameh in Mastering embedded systems diploma

#include <platform_Types.h>

extern int main(void);

void Reset_Handler(void);

void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void H_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MM_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Bus_fault(void) __attribute__((weak, alias("Default_Handler")));
void Usage_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));

//reserve stack 
static uint32 Stack_top[256];

void (* const vectors_arr[])(void) __attribute__((section(".vectors"))) = {
	(void(*)(void)) 	((uint32)Stack_top + (uint32)sizeof(Stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_fault_Handler,
	&MM_fault_Handler,
	&Bus_fault,
	&Usage_fault_Handler
};


extern uint32 _E_text;
extern uint32 _S_data;
extern uint32 _E_data;
extern uint32 _S_bss;
extern uint32 _E_bss;


void Reset_Handler(void)
{
	// copy data section from flash to ram
	uint32 DataSize = (uint8 *)&_E_data - (uint8 *)& _S_data;
	uint8 *P_src = (uint8 *)&_E_text;
	uint8 *P_dst = (uint8 *)&_S_data;
	uint32 i;
	for(i = 0; i < DataSize; i++)
	{
		*((uint8 *)P_dst++) = *((uint8 *)P_src++);
	}

	// initialize the bss section with zeros
	uint32 BssSize = (uint8 *) &(_E_bss) - (uint8 *) &(_S_bss);
	P_dst = (uint8*) &(_S_bss);
	for(i = 0; i < BssSize; i++)
	{
		*((uint8 *)P_dst++) = (uint8)0;
	}

	// jump to main
	main();
}

 