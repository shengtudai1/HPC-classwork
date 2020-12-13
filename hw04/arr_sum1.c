#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#define N 100000000
int arr[N];
int main(){
	double start, end;
	int NUM_THREADS = omp_get_max_threads();
	int i = 0;
	long long* a = NULL;
	#pragma omp parallel private(i)
	{int id = omp_get_thread_num();
	for(i=id;i<N;i+=NUM_THREADS)
		arr[i] = i+1;
	}
	a = (long long *)malloc(sizeof(long long)*NUM_THREADS);
	long long sum = 0;
	double k = 0;	
	start = omp_get_wtime();
	#pragma omp parallel private(i)
	{int id = omp_get_thread_num();
	for(i=id,a[id]=0;i<N-2;i+=NUM_THREADS){
		a[id] += (arr[i]+arr[i+1]+arr[i+2]);		
	}
	}
	for(i=0;i<NUM_THREADS;i++){
		sum += a[i]; 
	}
	k = sum/2.0;
	free(a); 
	a=NULL;
	end = omp_get_wtime();
	printf("%d\t%lf\t%f\n",NUM_THREADS,k,end-start);
	return 0;
}
