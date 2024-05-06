CC = gcc
CFLAGS = -Wall -Wextra

project10_scheduler: job.o project10_scheduler.o
	$(CC) $^ -o $@

job.o: job.c
	$(CC) $(CFLAGS) -c $< -o $@

project10_scheduler.o: project10_scheduler.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f job.o project10_scheduler.o project10_scheduler
