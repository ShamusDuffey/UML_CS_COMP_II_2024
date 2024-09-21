/**********************************************************************
Program: Number Filter
Author: Shamus Duffey
Date: <date you finish the program>
Time spent: <total amount of time spent on the project>
Purpose: The purpose of this program is to blah blah blah
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Bitflags.h"
#define flag 2000000000

int main(int argc, char* argv[])
{
	BIT_FLAGS storage = bit_flags_init_number_of_bits(flag);
	int input = 0;
	while(1)
	{
		scanf("%d", &input);
		if(input < 0)
			break;
		bit_flags_set_flag(storage, input);
	}
	printf("List:\n");
	for(int i = 0; i < flag; i++)
	{
		if(bit_flags_check_flag(storage, i))
		{
			printf("%d\n", i);
		}
	}
	bit_flags_destroy(&storage);
	return 0;
}