// Scott Enzinna
// OS project 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h> 

#include "mab.c"
#include "rsrc.c"
#include "PCB.c"



int dispatcherTimer;

// current
PcbPtr current;
PcbPtr psque;
PcbPtr userque;
PcbPtr next;
PcbPtr real;

// feedback queues
PcbPtr fb_que1;
PcbPtr fb_que2;
PcbPtr fb_que3;

// Memory
MabPtr mab_mem;
MabPtr tm;
MabPtr mab_real;

int main(int argc, char *argv[])
{
	// if no file was entered
	if (argc < 2)
	{
		printf("No file was entered\n");
	}
	
	// read from file
	else
	{
		FILE *fp;
		fp = fopen(argv[1],"r");
		if (fp == NULL)
		{
			printf("Error readin from file %s\n",argv[1]);
		}
		else
		{
			char buff[1024];
			PcbPtr ps_file;
			
			while(fgets(buff,sizeof(buff),fp) != NULL)
			{
				ps_file = createnullPcb();
				
				(*ps_file).arrivaltime = atoi(strtok(buff,", "));
				(*ps_file).priority = atoi(strtok(NULL,", "));
				(*ps_file).remainingcputime = atoi(strtok(NULL,", "));
				(*ps_file).memAlloc = atoi(strtok(NULL,", "));
				(*ps_file).Rs.printer = atoi(strtok(NULL,", "));
				(*ps_file).Rs.scanner = atoi(strtok(NULL,", "));
				(*ps_file).Rs.modem= atoi(strtok(NULL,", "));
				(*ps_file).Rs.cd = atoi(strtok(NULL,", "));
				
				PcbPtr temp;
				temp = enqPcb(psque, ps_file);
				psque = temp;
			}
		}
	}
	
	// set vales
	mab_mem = memInitialise( 64 , 1024 );
	mab_real = memInitialise(0,64);
	Rs.printer = 1+1;
	Rs.cd = 1+1;
	Rs.scanner = 1;
	Rs.modem = 1;
	
	// Run the process on the queues
	while(psque || current || userque || real || fb_que1 || fb_que2 || fb_que3)
	{
		while (psque && (*psque).arrivaltime <= dispatcherTimer)
		{
			int lvl = 0;
			lvl = (*psque).priority;
			
			if (lvl == 0)
			{
				PcbPtr enq;
				enq = enqPcb( real, deqPcb(&psque));
				real = enq;
				(*real).memory = memAlloc(mab_real, 64);
			}
			
			if (lvl != 0)
			{
				PcbPtr mp;
				mp = deqPcb(&psque);
				PcbPtr nt;
				nt = enqPcb(userque, mp);
				userque = nt;
			}
		}
		
		// prioority
		while (userque && (tm = memChk(mab_mem, (*userque).memAlloc)) && set(userque))
		{
		next = deqPcb(&userque);
		(*next).memory = memAlloc(tm, (*next).memAlloc);
		IO_Alloc(next);
		
		
		int pro;
		pro = (*next).priority;
		
		if (pro == 1)
		{
			PcbPtr p;
			p = enqPcb(fb_que1,next);
			fb_que1 = p;			
		}
		else if (pro == 2)
		{
			PcbPtr p;
			p = enqPcb(fb_que2,next);
			fb_que2 = p;
		}
		else
		{
			PcbPtr p;
			p = enqPcb(fb_que3,next);
			fb_que3 = p;
		}
		
		}
		
		// if current process
		if(current)
			{
				(*current).remainingcputime = (*current).remainingcputime -1;
				
				int time;
				time = (*current).remainingcputime;
                if (time == 0)
				{
					PcbPtr t;
					t = terminatePcb(current);
					current = t;
					free(current);
				}
				
				else if (fb_que1 || fb_que2 || fb_que3)
				{
					int important;
					important = ((*current).priority);
						
					if (important == 1)
					{
						PcbPtr mp;
						PcbPtr xt;
						
						mp = PausePcb(current);
						xt = enqPcb( fb_que2 , mp);
						
						fb_que2 = xt;
					}
					
					if (important != 1)
					{
					PcbPtr mp;
					PcbPtr xt;
					
					mp = PausePcb(current);
					xt = enqPcb( fb_que3 , mp);
					
					fb_que3 = xt;
					}
				

					int check;
					check = (*current).priority;
				
					if ( check < 3)
					{
						(*current).priority = (*current).priority + 1;
					}
					
					current = NULL;
				}
			}
			
			// if not current process
			if (!current)
			{
				if (real)
				{
					PcbPtr temp_;
					temp_ = deqPcb(&real);
					current = temp_;
					startPcb(current);
				}
				
				else if (fb_que1)
				{
					PcbPtr temp_;
					temp_ = deqPcb(&fb_que1);
					current = temp_;
					startPcb(current);
				}
				
				
				else if (fb_que2)
				{
					PcbPtr temp_;
					temp_ = deqPcb(&fb_que2);
					current = temp_;
					startPcb(current);
				}
				
				
				else if (fb_que3)
				{
					PcbPtr temp_;
					temp_ = deqPcb(&fb_que3);
					current = temp_;
					startPcb(current);
				}
			}
			// sleep
			system("sleep 1");
            dispatcherTimer++;
		}
	return 0;
}
