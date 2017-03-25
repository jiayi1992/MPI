#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int main() {

	int number;
	int maxN;
	int *souceArray;
	struct timeval tvs,tve;
	int i;
	double time;

	maxN = 0;
	FILE *fp = fopen("numbers.txt", "rt+"); 
	if(fp == NULL) {
		printf("open file failed");
		return 0;
	}else{  
		fscanf(fp,"%d",&number);
	}
	souceArray=(int *)malloc(sizeof(int)*number);
	memset(souceArray, 0, sizeof(int)*number); 
	for(i=0;i<number;i++)
	{
		fscanf(fp,"%d",&souceArray[i]);
	}
	//start time
	gettimeofday(&tvs,NULL);

	for(i = 0; i<number;i++)
	{
		if(souceArray[i]>maxN) maxN=souceArray[i];
	}

	//end time
	gettimeofday(&tve,NULL);
	time= tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;

	printf("time: %.12f seconds\n",time);
	printf("Proc root reporting : The max number = %d \n", maxN);

	return 0;

}
