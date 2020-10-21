#include "rsrc.h"

// Check to see if their are enough resources
int set(PcbPtr ps)
{
	if( (Rs.scanner < ps->Rs.scanner) || (Rs.printer < ps->Rs.printer) || (Rs.cd < ps->Rs.cd) || (Rs.modem < ps->Rs.modem) )
	{
		return 0;
	}
	else
	{
		return 1; 	
	}
}

// Allocate resources
void IO_Alloc(PcbPtr ps)
{
	Rs.printer = Rs.printer - ps->Rs.printer;
	Rs.scanner = Rs.scanner - ps->Rs.scanner;
	Rs.modem = Rs.modem - ps->Rs.modem;
	Rs.cd = Rs.cd - ps->Rs.cd;
	
}

// Free the recources used
void IO_Free(PcbPtr ps)
{
	Rs.printer = Rs.printer + ps->Rs.printer;
	Rs.scanner = Rs.scanner + ps->Rs.scanner;
	Rs.modem = Rs.modem + ps->Rs.modem;
	Rs.cd = Rs.cd + ps->Rs.cd;
}