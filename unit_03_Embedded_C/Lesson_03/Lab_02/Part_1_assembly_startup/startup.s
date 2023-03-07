/*
	Author: Ahmed Sameh Elshahed
	Assginment: lesson 3 lab 2 
	file name: startup.s
	description: this file is a startup file made for stm32F

*/

.section .vectors

.word 0x2000101c 		/* address of the top of the stack which will be saved in sp register */
.word _reset			/* 1 Reset handler */
.word Vector_handler	/* 2 NMI handler */
.word Vector_handler	/* 3 Hard Fault*/
.word Vector_handler	/* 4 MM Fault */
.word Vector_handler	/* 5 Bus Fault */
.word Vector_handler	/* 6 Usage Fault */
.word Vector_handler	/* 7 Reserved */
.word Vector_handler	/* 8 Reserved */
.word Vector_handler	/* 9 Reserved */
.word Vector_handler	/* 10 Reserved */
.word Vector_handler	/* 11 SV call */
.word Vector_handler	/* 12 Debug reserved*/
.word Vector_handler	/* 13 RESERVED */
.word Vector_handler	/* 14 PendSV */
.word Vector_handler	/* 15 SysTick */
.word Vector_handler	/* 16 IRQ0 */
.word Vector_handler	/* 17 IRQ1 */
.word Vector_handler	/* 18 IRQ2 */
.word Vector_handler	/* 19 ... */

/* and so on until IRQ67*/


.section .text
_reset:
	bl main
	b .


.thumb_func



Vector_handler:
	b _reset	