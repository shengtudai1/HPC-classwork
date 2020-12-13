#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "omp.h"
#include "time.h"
typedef struct{
float value;
int index;
} mess;
int main(int argc, char* argv[]){
	int i, N;
	N = atoi(argv[1]);
	double t0, t1;
	int world_rank, world_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

	mess* arr = NULL;
	arr = (mess*)malloc(sizeof(mess)*(N/world_size)+1);
        if(arr==NULL){
                printf("内存分配失败\n");
                exit(-1);
                }

	srand(10*world_rank);
	int j = 0;
	#pragma omp parallel for
	for(i=0;i<N;i+=world_size){
		arr[j].value = 0+1.0*rand()/RAND_MAX *(1000000-0);
		arr[j].index = i+world_rank*N;
		j++;
	}
	arr = (mess*)realloc(arr,j*sizeof(mess));

	t0 = MPI_Wtime();
	mess max, min, out;
	max = min=arr[0];
	for(i=0;i<j;i++){
		if(max.value<arr[i].value)
			max = arr[i];
		if(min.value>arr[i].value)
			min = arr[i];
	}
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Reduce(&max,&out,1,MPI_FLOAT_INT,MPI_MAXLOC,0,MPI_COMM_WORLD);
	t1 = MPI_Wtime();
	if(world_rank==0)	
	printf("maxrank=%d,maxindex=%d,maxvalue=%g,time=%g(s)\n",out.index/N,out.index%N,out.value,t1-t0);
	return MPI_Finalize();
}

