// Scott Enzinna
// Mab.h

#ifndef mab_h
#define mab_h

// given from PDF
typedef struct mab
{
	int offset;
	int size;
	int allocated;
    struct mab * next;
	struct mab * prev;
} Mab;
typedef Mab * MabPtr;


// Functinons
MabPtr memChk(MabPtr, int);
MabPtr memInitialise(int, int);
MabPtr memAlloc(MabPtr, int);
MabPtr memFree(MabPtr);
MabPtr memMerge(MabPtr);
MabPtr memSplit(MabPtr, int);
#endif
