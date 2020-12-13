#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
long long num_steps = 1000000000;
double step;
int main(int argc, char* argv[]) {
	double *sum;
	double t1, t2;
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();
	int world_rank, world_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	sum = (double*)malloc(sizeof(double)*world_size);
	int i;
	double x,pi = 0.0;
	step = 1.0/(double)num_steps;
	for(i=world_rank,sum[world_rank]=0; i<=num_steps; i+=world_size) {
		x = (i-0.5)*step;
		sum[world_rank] += 4.0/(1.0+x*x);
	}
	for(i=0; i<world_size; i++)
		MPI_Bcast(sum+i,1,MPI_DOUBLE,i,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(world_rank==0) {
		for(i=0; i<world_size; i++) {
			pi += sum[i]*step;
		}
		t2 = MPI_Wtime();
		printf("%d\t%f\t%f\n",world_size, pi,t2-t1);
	}
	return MPI_Finalize();
}
