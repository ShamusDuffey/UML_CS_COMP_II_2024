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

int main(int argc, char* argv[])//index is currently a negative value sometimes
{
	BIT_FLAGS storage = bit_flags_init_number_of_bits(2000000000);
	printf("Start: %d\n", bit_flags_check_flag(storage, 1999999999));
	bit_flags_set_flag(storage, 999999999);
	printf("End: %d\n", bit_flags_check_flag(storage, 1999999999));
	bit_flags_unset_flag(storage, 999999999);
	printf("After unsetting: %d\n", bit_flags_check_flag(storage, 1999999999));
	bit_flags_destroy(&storage);
	return 0;
}
