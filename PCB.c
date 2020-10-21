// Scott Enzinna
// OS project 2

#include "PCB.h"

PcbPtr startPcb(PcbPtr ps) {

if((*ps).state == Process_SUSPENDED )
{
	if(kill((*ps).pid, SIGCONT))
	{
		printf("%d Did not resume\n",(*ps).pid);
		return NULL;
	}
	
	(*ps).state = Process_RUNNING;
	return ps;
}

// fork 
int pid;
switch(pid = fork())
{
	case -1:
		printf("ERROR\n");
		return NULL;
		break;
		
	case 0:
		(*ps).pid = getpid();
		(*ps).state = Process_RUNNING;
		PrintPS(ps,(*ps).memory);
		execvp((*ps).args[0], (*ps).args);
		break;
		
	default:
		(*ps).pid = pid;
		(*ps).state = Process_RUNNING;
		break;
}
		return ps;
}


// Stop a process
PcbPtr terminatePcb(PcbPtr ps) {
		int status;
        if(kill((*ps).pid, SIGINT))
		{
			printf("Faild to terminate %d\n", (*ps).pid);
			return NULL;
        }

	(*ps).state = Process_TERMINATED;
	memFree((*ps).memory);
	IO_Free(ps);
	waitpid((*ps).pid, &status, WUNTRACED);
	return NULL;
}

// Create a null PCB
PcbPtr createnullPcb() {
        PcbPtr new;
        if( (new = malloc(sizeof(Pcb))) ) {
                (*new).args[0] = "./process";
                (*new).args[1] = NULL;        

                (*new).arrivaltime = 0;
                (*new).priority = 0;
                (*new).memAlloc = 0;
                (*new).remainingcputime = 0;
                (*new).Rs.printer = 0;
                (*new).Rs.scanner = 0;
                (*new).Rs.modem= 0;
                (*new).Rs.cd = 0;
				(*new).state = Process_CREATED;
				(*new).next = NULL;
                return new;
        }
		else
		{
			return NULL;
        }
}

// Print process information
void PrintPS(PcbPtr ps, MabPtr m)
{
	char *Current_State[] = {"CREATED","SUSPENDED","RUNNING","TERMINATED"};
	printf("pid   arrive  prior  cpu  memory printer  scanner  modem  cd   state");
	printf("\n");
	printf("%d   %d      %d      %d      %d     %d         %d      %d    %d   %d  %s\n",
	(*ps).pid,
	(*ps).arrivaltime,
	(*ps).priority,
	(*ps).remainingcputime,
	(*m).offset,
	(*ps).memAlloc,
	(*ps).Rs.printer,
	(*ps).Rs.scanner,
	(*ps).Rs.modem,
	(*ps).Rs.cd,
	Current_State[(*ps).state]
	);
}

// enque a process
PcbPtr enqPcb (PcbPtr head, PcbPtr ps) {
        if (head == NULL)
		{
			head = ps;
        }
		else if (head != NULL)
		{
			PcbPtr current;
			current = head;
			while ((*current).next)
			{
				current = (*current).next;
			}
			
			(*current).next = ps;                        
        }

        return head;
}
  
// Deque a process
PcbPtr deqPcb (PcbPtr *head) {
        if(head == NULL)
		{
			printf("Empty\n");
			return NULL;
        }
		
		PcbPtr current = *head;
		*head = (*head)->next;
		(*current).next = NULL;
		return current;
}

// Pause a process
PcbPtr PausePcb ( PcbPtr ps)
{
	int status;
	if (kill((*ps).pid,SIGTSTP))
	{
		printf("%d did not suspend\n",(*ps).pid);
		return NULL;
	}
	
	(*ps).state = Process_SUSPENDED;
	waitpid((*ps).pid,&status,WUNTRACED);
	return ps;
}