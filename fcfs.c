#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define JOB_SIZE (16)

typedef struct Job {
	unsigned int arrivalTime;
	unsigned int executionTime;
	unsigned int startTime;
	unsigned int endTime;
} Job;


void sort ( Job *jobs, int n) {

	for(int i = 0; i < n-1; i++) {
		bool swap = false;
		for(int j = 0; j < n-1; j++) {
			if(jobs[j].arrivalTime > jobs[j+1].arrivalTime) {
				Job tempJob = jobs[j];
				jobs[j] = jobs[j+1];
				jobs[j+1] = tempJob;
				swap = true;
			}
		}
		if(!swap) {
			break;
		}
		
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

	for(int i = 0; i < numberJobs; i++) {
		printf("For job number %d arrival is %u and execution is %u\n", i, jobs[i].arrivalTime, jobs[i].executionTime);

	}
	printf("\n");

	sort(jobs,numberJobs);

	for(int i = 0; i < numberJobs; i++) {
		printf("For job number %d arrival is %u and execution is %u\n", i, jobs[i].arrivalTime, jobs[i].executionTime);

	}



	return 0;


}

