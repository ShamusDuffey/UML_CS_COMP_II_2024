#include <stdio.h>
#include <stdlib.h>
#include "Bitflags.h"

#define POINTER_BUILD BitFlags* pBitFlags = (BitFlags*)hBit_flags;
int BYTES_PER_INTEGER = sizeof(int);
int BITS_PER_INTEGER = 8 * sizeof(int);
typedef struct bitFlags
{
	int* num;
	int size, capacity, bytesUsed;
}BitFlags;
int findBytesUsed(int bits)//totally legit function, has been stepped through
{
	if (bits < 0)
		return -1;
	int bytesUsed = 0;
	if (bits % BITS_PER_INTEGER == 0)
	{
		bytesUsed = bits / 8;
	}
	else
	{
		while (bits % BITS_PER_INTEGER != 0)
			bits++;
		bytesUsed = bits / 8;
	}
	return bytesUsed;
}
int findIntsUsed(int bits)
{
	if (bits < 0)
		return -1;
	int intsUsed = 0;
	if (bits % BITS_PER_INTEGER == 0)
	{
		intsUsed = bits / BITS_PER_INTEGER;
	}
	else
	{
		while (bits % BITS_PER_INTEGER != 0)
			bits++;
		intsUsed = bits / BITS_PER_INTEGER;
	}
	return intsUsed;
}
int roundUp(int a, int b)
{
	return ((a + b - 1) / b);
}
//Intentionally leaving out a default init function to force user to at least guess at the size needed.
//If one WERE to be used it would have the following prototype:
//BIT_FLAGS bit_flags_init_default(void);
//Precondition: number of bits is a positive integer.
//Postcondition: Returns the handle to a valid Bit_flags object that has the ability to store up to
// number_of_bits bits but currently all flags are set at zero. Returns NULL on failure. The container
// is assumed to hold size=number_of_bits after the init function runs.
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	BitFlags* pBitFlags = (BitFlags*)malloc(sizeof(BitFlags));
	if (pBitFlags == NULL)
		return NULL;
	pBitFlags->bytesUsed = findBytesUsed(number_of_bits);
	pBitFlags->num = (int*)malloc(pBitFlags->bytesUsed);
	if (!pBitFlags->num)
	{
		printf("There's no space to store that many bits"); exit(1);
	}
	for (int i = 0; i < pBitFlags->bytesUsed/BYTES_PER_INTEGER; i++)
	{
		pBitFlags->num[i] = 0;
	}
	pBitFlags->size = number_of_bits;
	pBitFlags->capacity = pBitFlags->bytesUsed * 8;
	return (BIT_FLAGS)pBitFlags;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 1. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation (except the one being set) will be set as zero.
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	if (hBit_flags == NULL) return 0;
		POINTER_BUILD
	if (flag_position >= pBitFlags->capacity)//resize protocall//doesn't work
	{
		int* biggerData = malloc(findIntsUsed(flag_position + 1) * BYTES_PER_INTEGER);
		if (!biggerData)
			return FAILURE;
		int i = 0;
		for (; i < pBitFlags->capacity / BITS_PER_INTEGER; i++)
		{
			biggerData[i] = pBitFlags->num[i];
		}
		for (; i < findIntsUsed(flag_position + 1) / BYTES_PER_INTEGER; i++)
		{
			biggerData[i] = 0;
		}
	}
	int index;
	if (flag_position % BITS_PER_INTEGER == 0)
		index = findIntsUsed(flag_position);
	else
		index = findIntsUsed(flag_position) - 1;
	int reference = 1;
	flag_position = (flag_position % BITS_PER_INTEGER);//the position of the flag within the index
	reference = reference << flag_position;
	pBitFlags->num[index] = pBitFlags->num[index] | reference;//current problem, crashes
	return SUCCESS;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 0. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation will be set as zero.
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	if (hBit_flags == NULL) return FAILURE;
		POINTER_BUILD
	if (flag_position >= pBitFlags->capacity)//resize protocall//doesn't work
	{
		int* biggerData = malloc(findIntsUsed(flag_position + 1) * BYTES_PER_INTEGER);
		if (!biggerData)
			return FAILURE;
		int i = 0;
		for (; i < pBitFlags->capacity / BITS_PER_INTEGER; i++)
		{
			biggerData[i] = pBitFlags->num[i];
		}
		for (; i < findIntsUsed(flag_position + 1) / BYTES_PER_INTEGER; i++)
		{
			biggerData[i] = 0;
		}
	}
	int index;
	if (flag_position % BITS_PER_INTEGER == 0)
		index = findIntsUsed(flag_position);
	else
		index = findIntsUsed(flag_position) - 1;
	int reference = 1;
	flag_position = (flag_position % BITS_PER_INTEGER);//the position of the flag within the index
	reference = reference << flag_position;
	pBitFlags->num[index] = (~reference) & (pBitFlags->num[index]);
	return SUCCESS;
}
//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the value of the flag at index flag_position if it is in bounds or -1 otherwise.
int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	printf("b=%d, ", flag_position);//
	if (hBit_flags == NULL) {return 0;}
	POINTER_BUILD
	/*if ((flag_position < 0) || (flag_position > pBitFlags->size))
	{
		printf("Flag position out of bounds\n"); return -1;
	}*/
	int index;
	if (flag_position % BITS_PER_INTEGER == 0)
		index = findIntsUsed(flag_position);
	else
		index = findIntsUsed(flag_position) - 1;
	flag_position %= BITS_PER_INTEGER;
	int reference = 1 << flag_position;
	printf("r=%d, i=%d, ", reference, index);//
	if ((pBitFlags->num[index]) & reference)//
		return 1;
	return 0;
}
//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits currently held by the data structure.
int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	if (hBit_flags == NULL) {return 0;}
	POINTER_BUILD

	return pBitFlags->size;
}
//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits the object CAN hold.
int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	if (hBit_flags == NULL) {return 0;}
	POINTER_BUILD
	return pBitFlags->capacity;
}
//Precondition: phBit_flags is the address of a handle to a valid Bit_flags object.
//Postcondition: The memory for the object referred to by the handle is free'd and the handle is set to NULL.
void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	if (phBit_flags == NULL)
	{
		printf("Null handle; nothing happened");
		return;
	}
	BitFlags* pBitFlags = (BitFlags*)*phBit_flags;
	free(pBitFlags->num);
	free(pBitFlags);
	*phBit_flags = NULL;
}