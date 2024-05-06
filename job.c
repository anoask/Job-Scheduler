#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "job.h"

void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority) {
	if (job_name != NULL) {
		printf("Enter the name of the job: ");
		scanf("%s", job_name);
	}
	if (user_name != NULL) {
		printf("Enter the name of the user: ");
		scanf("%s", user_name);
	}
	if (num_cpus != NULL) {
		printf("Enter the number of CPUs: ");
		scanf("%d", num_cpus);
	}
	if (num_gpus != NULL) {
		printf("Enter the number of GPUs: ");
		scanf("%d", num_gpus);
	}
	if (memory != NULL) {
		printf("Enter the amount of memory: ");
		scanf("%d", memory);
	}
	if (time != NULL) {
		printf("Enter the amount of time: ");
		scanf("%lf", time);
	}
	if (priority != NULL) {
		printf("Enter the priority: ");
		scanf("%d", priority);
	}
}

struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority) {
    struct job *new_job = (struct job *) malloc(sizeof(struct job));
    if (new_job == NULL) {
        printf("Error: out of memory\n");
        return scheduler;
    }

    // initialize the new job
    strcpy(new_job->job_name, job_name);
    strcpy(new_job->user_name, user_name);
    new_job->num_cpus = num_cpus;
    new_job->num_gpus = num_gpus;
    new_job->memory = memory;
    new_job->time = time;
    new_job->priority = priority;
    new_job->next = NULL;

    // add the new job to the end of the list
    if (scheduler == NULL) {
        // if the scheduler is empty, the new job becomes the first job
        scheduler = new_job;
    } else {
        struct job *current_job = scheduler, *previous_job = NULL;

        // traverse the scheduler list until a job with a lower priority than the new job is found
        while (current_job != NULL && priority <= current_job->priority) {
            previous_job = current_job;
            current_job = current_job->next;
        }

        if (previous_job == NULL) {
            // if the new job has the highest priority, it becomes the first job
            new_job->next = scheduler;
            scheduler = new_job;
        } else {
            // insert the new job between the previous job and the current job
            previous_job->next = new_job;
            new_job->next = current_job;
        }
    }

    return scheduler;
}


struct job * pop_job(struct job *scheduler) {
	
	struct job * popped_job = NULL;

	if (scheduler == NULL) {
		return NULL;
	}

	popped_job = scheduler;
	scheduler = scheduler->next;
	popped_job->next = NULL;

	// output format
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", popped_job->job_name, popped_job->user_name, popped_job->num_cpus, popped_job->num_gpus, popped_job->memory, popped_job->time, popped_job->priority);
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");

	return scheduler;
}

void list_user(struct job *scheduler, char *user_name) {
		

    struct job *current_job = scheduler;
    int header_printed = 0;
    
    while (current_job != NULL) {
        if (strcmp(user_name, current_job->user_name) == 0) {
            if (header_printed == 0) {
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
                printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n"); 
                header_printed = 1;
            }
            printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", current_job->job_name, current_job->user_name, current_job->num_cpus, current_job->num_gpus, current_job->memory, current_job->time, current_job->priority);
            printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
        }
        current_job = current_job->next;
    }
}

void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time) {

	struct job *current_job = scheduler;
	int header_printed = 0;
	while (current_job != NULL) {
		if (current_job->num_cpus <= num_cpus && current_job->num_gpus <= num_gpus &&
			current_job->memory <= memory && current_job->time <= time) {
				if (header_printed == 0) {
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
                printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n"); 
                header_printed = 1;
            }
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", current_job->job_name, current_job->user_name, current_job->num_cpus, current_job->num_gpus, current_job->memory, current_job->time, current_job->priority);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		}
		current_job = current_job->next;
	}
	if (header_printed == 0){
		//nothing
	}
}

void list_all_jobs(struct job *scheduler) {
    if (scheduler == NULL) {
        
        return;
    }

    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");

    struct job *current_job = scheduler;
    while (current_job != NULL) {
        printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", current_job->job_name, current_job->user_name, current_job->num_cpus, current_job->num_gpus, current_job->memory, current_job->time, current_job->priority);
        printf("|----------------------|----------------------|------|------|------|--------|----------|\n");

        current_job = current_job->next;
    }
}



struct job * clear_jobs(struct job *scheduler) {
	
	struct job *current_job = scheduler;
	while (current_job != NULL) {
		struct job *next_job = current_job->next;
		free(current_job);
		current_job = next_job;
	}
	return NULL;
}