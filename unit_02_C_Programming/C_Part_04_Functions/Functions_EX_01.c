/*
 *
 *  	Created on: 16 Jan 2023
 *      Author: Ahmed Sameh
 *      Problem statement: Print Prime numbers between two intervals by making user defined function
 */

#include <stdio.h>

char is_prime(int num);


int main(void)
{
	int lower_bound = 0, upper_bound = 0;
	printf("Enter two numbers(intervals): ");
	fflush(stdout);
	scanf("%d", &lower_bound);
	scanf("%d", &upper_bound);

	if(lower_bound > upper_bound)
	{
		lower_bound = lower_bound ^ upper_bound;
		upper_bound = lower_bound ^ upper_bound;
		lower_bound = lower_bound ^ upper_bound;
	}


	printf("Prime numbers between %d and %d are: ", lower_bound, upper_bound);
	for(int i = lower_bound; i <= upper_bound; i++)
	{
		if((i > 2 && i %2 == 0) || (! is_prime(i)))
			continue;
		printf("%d ", i);
	}
	return 0;
}

// this function will return 1 if the number is prime otherwise false
char is_prime(int num)
{
	int max_loop_count = num /2;

	for(int i = 2; i <= max_loop_count; i++)
	{
		if( num % i == 0)
			return 0;
	}

	return 1;
}
