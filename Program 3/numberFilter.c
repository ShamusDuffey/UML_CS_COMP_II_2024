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
#define flag 32

int main(int argc, char* argv[])//index is currently a negative value sometimes
{
	BIT_FLAGS storage = bit_flags_init_number_of_bits(flag);
	printf("Flag position %d at the start: %d\n", flag, bit_flags_check_flag(storage, flag));
	bit_flags_print(storage);
	bit_flags_set_flag(storage, flag);
	printf("Flag position %d at the end: %d\n", flag, bit_flags_check_flag(storage, flag));
	bit_flags_print(storage);
	bit_flags_unset_flag(storage, flag);
	printf("After unsetting flag position %d its value is: %d\n", flag, bit_flags_check_flag(storage, flag));
	bit_flags_print(storage);
	bit_flags_destroy(&storage);
	return 0;
}