#include <stdio.h>
#include <stdlib.h>

#define JOB_SIZE (16)

typedef struct Job {
	unsigned int arrivalTime;
	unsigned int executionTime;
	unsigned int startTime;
	unsigned int endTime;
} Job;


void sort ( Job *jobs, int n) {

	for(int i = 0; i < n; i++) {
		
	
	}
	



} 

int main (int argc, char *argv[]) {

	FILE *file;
	file = fopen(argv[1],"r");
	if(file == NULL) {
		perror("fopen");
	}

	unsigned int numberJobs;		// the number of jobs
	fscanf(file, "%u", &numberJobs);

	Job *jobs;
	jobs = (Job *)malloc(JOB_SIZE * numberJobs);

	unsigned int tempNumber;
	for(int i = 0; fscanf(file, "%u",&tempNumber) != EOF; i++) {
		jobs[i].arrivalTime = tempNumber;
		fscanf(file, "%u", &tempNumber);
		jobs[i].executionTime = tempNumber;

	} 

	sort(*jobs,numberJobs);

	return 0;


}

