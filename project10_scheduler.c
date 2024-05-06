/*
Anosh Askari
The following program contains only the main function for a FIFO-based
simple scheduler. It is split into another source file and a header file,
named job.c and job.h respectively.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "job.h"

void help();

int main() {
	char code;
	char job_name[NAME_LEN + 1], user_name[NAME_LEN + 1];
	int num_cpus, num_gpus, memory, priority;
	double time;

	struct job *scheduler = NULL;

	help();
	printf("\n");

	for (;;) {
		// read operation code
		printf("Enter operation code: ");
		scanf(" %c", &code);
		while (getchar() != '\n') /* skips to end of line */
			;

		// run operation
		switch (code) {
		case 'h':
			help();
			break;
		case 'a':
			read(job_name, user_name, &num_cpus, &num_gpus, &memory, &time, &priority);
			scheduler = add_job(scheduler, job_name, user_name, num_cpus, num_gpus, memory, time, priority);
			break;
		case 'p':
			scheduler = pop_job(scheduler);
			break;
		case 'u':
			read(NULL, user_name, NULL, NULL, NULL, NULL, NULL);
			list_user(scheduler, user_name);
			break;
		case 'j':
			read(NULL, NULL, &num_cpus, &num_gpus, &memory, &time, NULL);
			list_jobs(scheduler, num_cpus, num_gpus, memory, time);
			break;
		case 'l':
			list_all_jobs(scheduler);
			break;
		case 'q':
			scheduler = clear_jobs(scheduler);
			return 0;
		default:
			printf("Illegal operation code!\n");
		}
		printf("\n");
	}
}

void help() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a job to the scheduler;\n");
	printf("\t'p' for removing a job from the scheduler;\n");
	printf("\t'u' for searching jobs per user;\n");
	printf("\t'j' for searching jobs per capacity;\n");
	printf("\t'l' for listing all jobs;\n");
	printf("\t'q' for quit.\n");
}