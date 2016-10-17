#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define JOB_SIZE (16)

typedef struct Job {
	unsigned int arrivalTime;
	unsigned int executionTime;
	unsigned int startTime;
	unsigned int finishTime;
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

	sort(jobs,numberJobs);

	jobs[0].startTime = jobs[0].arrivalTime;
	jobs[0].finishTime = jobs[0].arrivalTime + jobs[0].executionTime;

	for(int i = 1; i < numberJobs; i++) {
		if(jobs[i].arrivalTime > jobs[i-1].finishTime) {
			jobs[i].startTime = jobs[i].arrivalTime;
		}
		else {
			jobs[i].startTime = jobs[i-1].finishTime;
		}
		jobs[i].finishTime = jobs[i].startTime + jobs[i].executionTime;
	}

	double averageTurnaround;
	double averageResponse;

	for(int i = 0; i < numberJobs; i++) {
		averageTurnaround += (double)(jobs[i].finishTime - jobs[i].arrivalTime);
		averageResponse   += (double)(jobs[i].startTime  - jobs[i].arrivalTime);
	}

	averageTurnaround = averageTurnaround / numberJobs;
	averageResponse   = averageResponse   / numberJobs;

	printf("%.5f\n", averageTurnaround);
	printf("%.5f\n", averageResponse);

	return 0;

}
