# host-dispatcher
The purpose of this project was to write a four-level priority process dispatcher operating within the
constraints of finite available memory and I/O resources.

## Date Complted
Fall 2013 - University of South Florida

## Project Requirements
- Real-Time processes must be run immediately on a First Come First Served (FCFS)
basis, pre-empting any other processes running with lower priority. These processes are
run till completion. 
- Normal user processes are run on a time sliced three-level feedback dispatcher. The
basic timing quantum of the dispatcher is 1 second. This is also the value for the time
quantum of the feedback scheduler.

#### The dispatcher controls the following resource:
- 2 Printers
- 1 Scanner
- 1 Modem
- 2 CD Drives
- 1024 Mbyte Memory available for processes
