#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include"mpi.h" 

int main(int argc, char *argv[]) {

	int MyProc, tag=1, size;
	int number=0;
	int length;
	int residual;
	int *souceArray = NULL;
	int maxFin;
	int maxN;
	int root;
	FILE *fp;
	MPI_Status status;
	struct timeval tvs,tve;

	root = 0;
	maxN = 0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyProc);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//get the number of numbers in the file
	if(MyProc == 0){
		fp = fopen("numbers.txt", "rt+"); 
		if(fp == NULL) {
			printf("open file failed");
			return 0;
		}else{  
			fscanf(fp,"%d",&number);
		}
	}

	//start time
	gettimeofday(&tvs,NULL);

	MPI_Bcast(&number, 1, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	souceArray=(int *)malloc(sizeof(int)*number);
	memset(souceArray, 0, sizeof(int)*number); 

	//put the data into matrix
	if(MyProc == 0){
		int i;
		for(i = 0; i < number; i++){
			fscanf(fp,"%d",&souceArray[i]);
		}
	}
	MPI_Bcast(souceArray, number, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	length = number / size;
	if(MyProc != (size-1)){
		int i = 0; 
		for(i = (MyProc)*length; i<(MyProc+1)*length;i++)
		{
			if(souceArray[i]>maxN) maxN=souceArray[i];
		}
		printf("Proc %d reporting : The max number = %d\n",MyProc,maxN);
	}
	else
	{
		int i=0;
		for(i = (MyProc)*length; i<number;i++)
		{
			if(souceArray[i]>maxN) maxN=souceArray[i];
		}
		printf("Proc %d reporting : The max number = %d\n",MyProc,maxN);
	}
	MPI_Reduce(&maxN, &maxFin, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	//end time
	gettimeofday(&tve,NULL);
	double time = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;
	if(MyProc == 0) {
		printf("There are %d processes\n",size);
		printf("Proc root reporting : The max number = %d\n",maxFin);
		printf("time: %.12f seconds\n",time);
	}
	
	MPI_Finalize();
}
