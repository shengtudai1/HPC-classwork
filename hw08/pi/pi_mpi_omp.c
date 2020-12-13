#include "mpi.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#define N 1000000000
int main(int argc, char* argv[]){
	int rank, nproc;
	int i, low, up;
	double local = 0.0, pi, w, temp, t0, t1, t2;
	int provided;
	MPI_Status status;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	t0 = MPI_Wtime();
	w = 1.0/N ; low = rank*(N/nproc); up = low +N/nproc - 1;
	#pragma omp parallel for reduction(+:local) private(temp,i)
	for (i=low;i<up;i++){
		temp = (i+0.5) * w;
		local = local + 4.0/(1.0+temp*temp);
	}
	MPI_Reduce(&local,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0) printf("pi=%.20f\n",pi*w);
	t1 = MPI_Wtime();
	if(rank==0) printf("time used = %.2f\n", t1-t0);
	return MPI_Finalize();
}
