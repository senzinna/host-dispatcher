#ifndef rsrc_h
#define rsrc_h

// Struct for resources
typedef struct rsrc
{
	int scanner;
	int modem;
	int cd;
	int printer;
} Rsrc;

#include "PCB.h"

// Function
Rsrc Rs;
void IO_Alloc(PcbPtr);
int set(PcbPtr);
void IO_Free(PcbPtr);

#endif