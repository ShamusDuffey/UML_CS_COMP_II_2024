/**********************************************************************
Program: Number Filter
Author: Shamus Duffey
Date: 9/21/2024
Time spent: 1 month
Purpose: This program takes a list of integers 2000000000 entries long and outputs a sorted list with the duplicates removed.
It uses a custom bitflags object to do so.
***********************************************************************/
#ifndef BITFLAGS
#define BITFLAGS
typedef enum status { FAILURE, SUCCESS }Status;
typedef void* BIT_FLAGS;
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits);
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position);
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position);
int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position);
int bit_flags_get_size(BIT_FLAGS hBit_flags);
int bit_flags_get_capacity(BIT_FLAGS hBit_flags);
void bit_flags_destroy(BIT_FLAGS* phBit_flags);
#endif