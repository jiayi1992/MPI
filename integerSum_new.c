/*  Generic summation of integers in a specified interval
   Author : Sumir Chandra @ Rutgers
*/

#include "mpi.h"
#include <stdio.h>

int main(argc,argv)
int argc;
char **argv;
{

  int MyProc, tag=1, size;
  char msg='A', msg_recpt ;
  MPI_Status *status ;
  int root ;
  int left=20, right=100, interval ;
  int number, start, end, sum, GrandTotal;
  int mystart, myend;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyProc);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  root = 0;
 
  MPI_Bcast(&left, 1, MPI_INT, root, MPI_COMM_WORLD);  /* Bcast limits to all */
  MPI_Bcast(&right, 1, MPI_INT, root, MPI_COMM_WORLD);

  if(((right - left + 1) % size) != 0)
  interval = (right - left + 1) / size + 1 ;  /* Fix local limits of summing */
  else
    interval = (right - left + 1) / size;
  mystart = left + MyProc*interval ;
  myend = mystart + interval ;
  /* set correct limits if interval is not a multiple of size */
  if (myend > right) myend = right + 1 ;

  sum = root;                      /* Sum locally on each proc */
  if (mystart <= right)
    for (number = mystart; number < myend; number++) sum = sum + number ;

  printf("proc %d : start = %d, end = %d sum= %d \n", MyProc, start, end, sum);

  /* Do reduction on proc root */
  MPI_Reduce(&sum, &GrandTotal, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD) ;

  MPI_Barrier(MPI_COMM_WORLD);

  /* Root reports the results */
  if(MyProc == root) 
	printf("Proc root reporting : Grand total = %d \n", GrandTotal);

  MPI_Finalize();
}
