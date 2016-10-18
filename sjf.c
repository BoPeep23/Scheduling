#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define JOB_SIZE (16)			// the size of the Job struct

typedef struct Job {
	unsigned int arrivalTime;	
	unsigned int executionTime;
	unsigned int startTime;		// time at first run
	unsigned int finishTime;	// time at run end
} Job;

void sort ( Job *jobs, int n) {
	Job tempJob;
	/* Using bubble sort because it has complexity of O(who cares),
	 * it's only sorting 100 items at max. */
	for(int i = 0; i < n-1; i++) {
		// swap ends the sort early if it's already sorted
		bool swap = false;
		// bubble sort!
		for(int j = 0; j < n-1; j++) {
			if(jobs[j].arrivalTime > jobs[j+1].arrivalTime) {
				tempJob = jobs[j];
				jobs[j] = jobs[j+1];
				jobs[j+1] = tempJob;
				swap = true;
			}
		}
		// list is sorted, we can stop
		if(!swap) {
			break;
		}
	}
}

int main (int argc, char *argv[]) {

	printf("Size: %d\n",sizeof(bool));	

	FILE *file;				// open it up
	file = fopen(argv[1],"r");
	if(file == NULL) {
		perror("fopen");
		exit(1);
	}

	unsigned int numberJobs;		// the number of jobs
	fscanf(file, "%u", &numberJobs);

	Job *jobs;				// keep everything here
	jobs = (Job *)malloc(JOB_SIZE * numberJobs);

	unsigned int tempNumber;
	/* Read in all of the data we need */
	for(int i = 0; fscanf(file, "%u",&tempNumber) != EOF; i++) {
		jobs[i].arrivalTime = tempNumber;
		fscanf(file, "%u", &tempNumber);
		jobs[i].executionTime = tempNumber;
	} 

	/* Sort it by arrival time */
	sort(jobs,numberJobs);

	/* Just hard code the first one as a base case */
//	jobs[0].startTime = jobs[0].arrivalTime;
//	jobs[0].finishTime = jobs[0].arrivalTime + jobs[0].executionTime;

	/* Uses some math to calculate the start/finish times */

	int time = jobs[0].arrivalTime;
	Job tempJob;
	for(int i = 0; i < numberJobs; i++) {
		unsigned int minTime = jobs[i].executionTime;
		int minIndex = i;
		printf("On index %d, time is %d\n",i, time);	
		printf("Defaults minTime is %d\n", minTime);
		for(int j = i; jobs[j].arrivalTime <= time && j < numberJobs; j++) {
			if(jobs[j].executionTime < jobs[minIndex].executionTime) {
				minTime  = jobs[j].executionTime;
				minIndex = j;
			}
		}
			tempJob = jobs[minIndex];
			jobs[minIndex] = jobs[i];
			jobs[i] = tempJob;	
			time += jobs[i].executionTime;

			printf("Minimum job is index %d with arrival time %d and execution time %d\n",minIndex,jobs[i].arrivalTime,jobs[i].executionTime); 

			if(i == 0) {
				jobs[i].startTime = jobs[i].arrivalTime;
				jobs[i].finishTime = jobs[i].arrivalTime + jobs[i].executionTime;
			}
			else {
				if(jobs[i].arrivalTime > jobs[i-1].finishTime) {
					jobs[i].startTime = jobs[i].arrivalTime;
				}
				else {
					jobs[i].startTime = jobs[i-1].finishTime;
				}
				jobs[i].finishTime = jobs[i].startTime + jobs[i].executionTime;
			}
	}

	
	for(int i = 0; i < numberJobs; i++) {
		printf("Arrival: %u Execute: %u Start: %u Finish: %u\n", jobs[i].arrivalTime, jobs[i].executionTime, jobs[i].startTime, jobs[i].finishTime);
		
	}

	double averageTurnaround;
	double averageResponse;

	/* Calculating the average times */
	for(int i = 0; i < numberJobs; i++) {
		averageTurnaround += 
			(double)(jobs[i].finishTime - jobs[i].arrivalTime);
		averageResponse   +=
			 (double)(jobs[i].startTime  - jobs[i].arrivalTime);
	}

	averageTurnaround = averageTurnaround / numberJobs;
	averageResponse   = averageResponse   / numberJobs;

	/* Done! */
	printf("%.5f\n", averageTurnaround);
	printf("%.5f\n", averageResponse);

	/* Look, good programming practices! */
	free(jobs);
	
	return 0;

}
