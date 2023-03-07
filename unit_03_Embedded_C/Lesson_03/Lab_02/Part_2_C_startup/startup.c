// created by Ahmed Sameh in Mastering embedded systems diploma

#include <platform_Types.h>

extern int main(void);

void Rest_Handler(void);

void Default_Handler()
{
	Rest_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void H_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MM_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Bus_fault(void) __attribute__((weak, alias("Default_Handler")));
void Usage_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
extern uint32 _stack_top;

uint32 vectors[] __attribute__((section(".vectors"))) = {
	(uint32) 	&_stack_top,
	(uint32)	&Rest_Handler,
	(uint32)	&NMI_Handler,
	(uint32)	&H_fault_Handler,
	(uint32)	&MM_fault_Handler,
	(uint32)	&Bus_fault,
	(uint32)	&Usage_fault_Handler
};

extern uint32 _E_text;
extern uint32 _S_data;
extern uint32 _E_data;
extern uint32 _S_bss;
extern uint32 _E_bss;


void Rest_Handler(void)
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

 