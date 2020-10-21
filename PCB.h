// Scott Enzinna
// OS project 2

#ifndef PCB_h
#define PCB_h

// State of process
typedef enum PROCESS_STATES {
	   Process_CREATED, 
	   Process_SUSPENDED, 
	   Process_RUNNING,
	   Process_TERMINATED,
} ps_states;

// Struct for process
typedef struct pcb
{
	pid_t pid;
	char *args[2];
	
	int arrivaltime;
	int priority;
	int memAlloc;
	int remainingcputime;
	
	struct rsrc Rs;
	struct mab * memory;
	ps_states state;
	struct pcb * next;
} Pcb;
typedef Pcb * PcbPtr;


// Functions
PcbPtr startPcb(PcbPtr);
PcbPtr terminatePcb(PcbPtr);
PcbPtr createnullPcb();
PcbPtr enqPcb (PcbPtr, PcbPtr);
PcbPtr deqPcb (PcbPtr*);
PcbPtr PausePcb (PcbPtr);
void PrintPS(PcbPtr, MabPtr);

#endif