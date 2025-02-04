# Job-Scheduler

Overview:

This program is a simple FIFO-based scheduler designed to manage jobs with various attributes such as name, user, CPU/GPU counts, memory, time, and priority. It provides basic functionality to add jobs, remove jobs, and list jobs based on different criteria like user or capacity.


Files:

main.c: Contains the main function and user interface logic. It prompts the user for operation codes and calls corresponding functions defined in job.c to perform operations on the scheduler.

job.c: Implements functions to manipulate the job scheduler. This includes functions to add jobs, remove jobs, list jobs by user, list jobs by capacity, list all jobs, and clear all jobs.

job.h: Declares the structure for a job and function prototypes for the functions defined in job.c.

Makefile: Provides rules for compiling the program. It compiles main.c and job.c into object files and links them together to create the executable project10_scheduler.
Compilation:


To compile the program, run the following command in the terminal:
make
This will generate the executable project10_scheduler.


Usage:
After compiling, execute the program by running:
./project10_scheduler


Once the program is running, follow the on-screen instructions to interact with the scheduler. The available operation codes are:

h: Display help menu.

a: Add a job to the scheduler.

p: Remove a job from the scheduler.

u: List jobs by user.

j: List jobs by capacity.

l: List all jobs.

q: Quit the program.
